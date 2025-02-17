// hpiinfo_cmd.cpp
//
// A Qt-based application for display information on ASI cards.
//
//   (C) Copyright 2002-2025 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <QCoreApplication>
#include <QTranslator>

#include "cmdswitch.h"
#include "hpiinfo_cmd.h"

MainObject::MainObject()
  :QObject()
{
  QString ui_format="%INDEX%: %NAME%";
  bool ok=false;

  hpi_adapter_quantity=0;
  
  //
  // Load the command-line arguments
  //
  CmdSwitch *cmd=new CmdSwitch("hpiinfo_cmd",HPIINFO_CMD_USAGE);
  for(unsigned i=0;i<cmd->keys();i++) {
    if(cmd->key(i)=="--index") {
      hpi_ui_indices.push_back(cmd->value(i).toInt(&ok)-1);
      if((!ok)||(hpi_ui_indices.back()<0)||(hpi_ui_indices.back()>=HPI_MAX_ADAPTERS)) {
	fprintf(stderr,"hpiinfo-cmd: invalid adapter index\n");
	exit(1);
      }
      cmd->setProcessed(i,true);
    }
    if(cmd->key(i)=="--format") {
      ui_format=cmd->value(i);
      cmd->setProcessed(i,true);
    }
    if(!cmd->processed(i)) {
      fprintf(stderr,"hpiinfo-cmd: unrecognized option \"%s\"\n",
	      cmd->key(i).toUtf8().constData());
      exit(1);
    }
  }

  //
  // Open HPI
  //
  if(HPI_SubSysCreate()==NULL) {
    fprintf(stderr,"hpiinfo-cmd: cannot access hpi subsystem\n");
    exit(1);
  }

  LoadAdapters();

  //
  // Default Output
  //
  if(hpi_ui_indices.isEmpty()) {
    for(int i=0;i<HPI_MAX_ADAPTERS;i++) {
      if(hpi_type[i]!=0) {
	printf("%s\n",ResolveFormat(i,ui_format).toUtf8().constData());
      }
    }
    exit(0);
  }

  for(int i=0;i<hpi_ui_indices.size();i++) {
    printf("%s\n",ResolveFormat(hpi_ui_indices.at(i),
				ui_format).toUtf8().constData());
  }
  
  exit(0);
}


void MainObject::LoadAdapters()
{
  uint32_t index=0;
  for(int i=0;i<HPI_MAX_ADAPTERS;i++) {
    hpi_type[i]=0;
    hpi_name[i]="[not present]";
    hpi_ostreams[i]=0;
    hpi_istreams[i]=0;
    hpi_card_version[i]=0;
    hpi_serial[i]=0;
    hpi_mode[i]=0;
  }
  HpiErr(HPI_SubSysGetVersionEx(NULL,&hpi_version),"HPI_SubSysGetVersionEx");
  HpiErr(HPI_SubSysGetNumAdapters(NULL,&hpi_adapter_quantity),
	 "HPI_SubSysGetNumAdapters");
  for(int i=0;i<hpi_adapter_quantity;i++) {
    HpiErr(HPI_SubSysGetAdapter(NULL,i,&index,hpi_type+i),
	   "HPI_SubSysGetAdapter");
    hpi_name[index]=QString::asprintf("AudioScience %X [%d]",hpi_type[i],i+1);
    if(hpi_type[i]!=0) {
      HpiErr(HPI_AdapterOpen(NULL,index),"HPI_AdapterOpen");
      HpiErr(HPI_AdapterGetInfo(NULL,index,&hpi_ostreams[index],
				&hpi_istreams[index],
				&hpi_card_version[index],hpi_serial+index,
				&hpi_type[index]),"HPI_AdapterGetInfo");
      HpiErr(HPI_AdapterGetMode(NULL,index,&hpi_mode[index]),
	     "HPI_AdapterGetMode");
      HpiErr(HPI_AdapterClose(NULL,index),"HPI_AdapterClose");
      HpiErr(HPI_ProfileOpenAll(NULL,index,0,&hpi_profile[index],
				&hpi_profile_quan[index]));
    }
  }
}


QString MainObject::ResolveFormat(int index,const QString &fmt) const
{
  QString ret;
  QString wildcard;
  
  ret=fmt;
  ret.replace("%HPI_VERSION%",
	      QString::asprintf("%d.%02d.%02d",
				(unsigned)((hpi_version>>16)&0xffff),
				(unsigned)((hpi_version>>8)&0xff),
				(unsigned)hpi_version&0xff));
  ret.replace("%INDEX%",QString::asprintf("%d",1+index));
  if(hpi_type[index]==0) {
    ret.replace("%MODEL%","0000");
    ret.replace("%NAME%","[not present]");
    ret.replace("%SERIAL%","0");
    ret.replace("%INPUT_STREAMS%","0");
    ret.replace("%OUTPUT_STREAMS%","0");
    ret.replace("%DSP_VERSION%","0.0");
    ret.replace("%HARDWARE_VERSION%","0");
  }
  else {
    ret.replace("%MODEL%",QString::asprintf("%X",hpi_type[index]));
    ret.replace("%NAME%",hpi_name[index]);
    ret.replace("%SERIAL%",QString::asprintf("%u",hpi_serial[index]));
    ret.replace("%INPUT_STREAMS%",QString::asprintf("%d",hpi_istreams[index]));
    ret.replace("%OUTPUT_STREAMS%",QString::asprintf("%d",hpi_ostreams[index]));
    ret.replace("%DSP_VERSION%",
		QString::asprintf("%d.%d",
				  hpi_card_version[index]>>13,
				  (hpi_card_version[index]>>7)&63));
    ret.replace("%HARDWARE_VERSION%",
		QString::asprintf("%c%d",
				  ((hpi_card_version[index]>>3)&15)+'A',
				  hpi_card_version[index]&7));
  }
  ret.replace("%%%","%");

  return ret;
}


hpi_err_t MainObject::HpiErr(hpi_err_t err,const char *func_name) const
{
  char hpi_str[200];

  if(err==HPI_ERROR_INVALID_FUNC) {
    return err;
  }
  if(err!=0) {
    HPI_GetErrorText(err,hpi_str);
    if(func_name==NULL) {
      fprintf(stderr,"hpiinfo_cmd: %s\n",hpi_str);
    }
    else {
      fprintf(stderr,"hpiinfo_cmd[%s]: %s\n",func_name,hpi_str);
    }
  }
  return err;
}


int main(int argc,char *argv[])
{
  QCoreApplication a(argc,argv);
  
  new MainObject();

  return a.exec();
}
