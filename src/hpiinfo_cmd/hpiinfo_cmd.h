// hpiinfo_cmd.h
//
// Command line utility for access HPI device information.
//
//   (C) Copyright 2025 Fred Gleason <fredg@paravelsystems.com>
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


#ifndef HPIINFO_CMD_H
#define HPIINFO_CMD_H

#include <QObject>

#include <asihpi/hpi.h>
#if HPI_VER < 0x040600
typedef uint16_t hpi_err_t;
typedef uint32_t hpi_handle_t;
#endif

#define HPIINFO_CMD_USAGE "\n"

class MainObject : public QObject
{
  Q_OBJECT
 public:
  MainObject();

 private:
  void LoadAdapters();
  QString ResolveFormat(int index,const QString &fmt) const;
  hpi_err_t HpiErr(hpi_err_t err,const char *func_name=0) const;
  QList<int> hpi_ui_indices;
  uint32_t hpi_version;
  int hpi_adapter_quantity;
  QString hpi_name[HPI_MAX_ADAPTERS];
  uint16_t hpi_ostreams[HPI_MAX_ADAPTERS];
  uint16_t hpi_istreams[HPI_MAX_ADAPTERS];
  uint16_t hpi_card_version[HPI_MAX_ADAPTERS];
  uint32_t hpi_serial[HPI_MAX_ADAPTERS];
  uint16_t hpi_type[HPI_MAX_ADAPTERS];
  uint32_t hpi_mode[HPI_MAX_ADAPTERS];
  hpi_handle_t hpi_profile[HPI_MAX_ADAPTERS];
  uint16_t hpi_profile_quan[HPI_MAX_ADAPTERS];
 };


#endif  // HPIINFO_CMD_H
