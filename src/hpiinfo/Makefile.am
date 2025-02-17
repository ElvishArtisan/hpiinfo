## automake.am
##
## Automake.am for src/
##
## (C) Copyright 2015-2025 Fred Gleason <fredg@paravelsystems.com>
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
##   Use automake to process this into a Makefile.in
##

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" -Wno-strict-aliasing -std=c++17 -fPIC @QT6_CFLAGS@
MOC = @QT6_MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	$(MOC) $< -o $@

sbin_PROGRAMS = hpiinfo

dist_hpiinfo_SOURCES = change_mode.cpp change_mode.h\
                       cmdswitch.cpp cmdswitch.h\
                       combobox.cpp combobox.h\
                       hpiinfo.cpp hpiinfo.h\
                       virtdetails.cpp virtdetails.h

nodist_hpiinfo_SOURCES = moc_change_mode.cpp\
                         moc_combobox.cpp\
                         moc_hpiinfo.cpp\
                         moc_virtdetails.cpp

hpiinfo_LDADD = @QT6_LIBS@ -lhpi

EXTRA_DIST = hpiinfo.pro

CLEANFILES = *~\
             *.qm\
             moc_*

MAINTAINERCLEANFILES = *~\
                       Makefile.in\
                       moc_*
