## automake.am
##
## xdg/automake.am for HPIInfo
##
##   (C) Copyright 2015 Fred Gleason <fredg@paravelsystems.com>
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
	mkdir -p $(DESTDIR)@prefix@/share/applications
	cp hpiinfo.desktop $(DESTDIR)@prefix@/share/applications/
	mkdir -p $(DESTDIR)/etc/pam.d
	cp hpiinfo-root-pam $(DESTDIR)/etc/pam.d/hpiinfo-root
	mkdir -p $(DESTDIR)/etc/security/console.apps
	cp hpiinfo-root-consolehelper $(DESTDIR)/etc/security/console.apps/hpiinfo-root
	rm -f $(DESTDIR)$(prefix)/sbin/hpiinfo-root
	ln -s /usr/bin/consolehelper $(DESTDIR)$(prefix)/sbin/hpiinfo-root

uninstall-local:	
	rm -f $(DESTDIR)@prefix@/share/applications/hpiinfo.desktop
	rm -f $(DESTDIR)/etc/security/console.apps/hpiinfo-root
	rm -f $(DESTDIR)$(prefix)/sbin/hpiinfo-root

EXTRA_DIST = hpiinfo.desktop\
             hpiinfo-root-consolehelper\
             hpiinfo-root-pam

CLEANFILES = *~

MAINTAINERCLEANFILES = *~\
                       Makefile.in
