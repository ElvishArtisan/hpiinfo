## Makefile.am
##
## Makefile.am for src/hpiinfo-cmd
##
## (C) Copyright 2025 Fred Gleason <fredg@paravelsystems.com>
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

bin_PROGRAMS = hpiinfo-cmd

dist_hpiinfo_cmd_SOURCES = cmdswitch.cpp cmdswitch.h\
                           hpiinfo_cmd.cpp hpiinfo_cmd.h

nodist_hpiinfo_cmd_SOURCES = moc_hpiinfo_cmd.cpp

hpiinfo_cmd_LDADD = @QT6_LIBS@ -lhpi

EXTRA_DIST = hpiinfo_cmd.pro

CLEANFILES = *~\
             *.qm\
             moc_*

MAINTAINERCLEANFILES = *~\
                       Makefile.in\
                       moc_*
