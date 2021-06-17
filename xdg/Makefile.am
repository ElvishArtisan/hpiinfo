## automake.am
##
## xdg/automake.am for HPIInfo
##
##   (C) Copyright 2015-2021 Fred Gleason <fredg@paravelsystems.com>
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License version 2 as
##   published by the Free Software Foundation.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public
##   License along with this program; if not, write to the Free Software
##   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
## Use automake to process this into a Makefile.in

install-exec-am:	
	./install_usermode.sh install $(DESTDIR) $(prefix)
	mkdir -p $(DESTDIR)@prefix@/share/applications
	cp @HPIINFO_DESKTOP_FILE@ $(DESTDIR)@prefix@/share/applications/hpiinfo.desktop

uninstall-local:	
	rm -f $(DESTDIR)@prefix@/share/applications/hpiinfo.desktop
	./install_usermode.sh uninstall $(DESTDIR) $(prefix)

EXTRA_DIST = hpiinfo.desktop\
             hpiinfo-root.desktop\
             hpiinfo-sudo.desktop\
             hpiinfo-root-consolehelper\
             hpiinfo-root-pam\
             install_usermode.sh.in

CLEANFILES = *~

DISTCLEANFILES = install_usermode.sh

MAINTAINERCLEANFILES = *~\
                       Makefile.in
