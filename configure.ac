dnl configure.ac
dnl
dnl Autoconf configuration
dnl
dnl Use autoconf to process this into a configure script
dnl
dnl   (C) Copyright 2015-2021 Fred Gleason <fredg@paravelsystems.com>
dnl
dnl   This program is free software; you can redistribute it and/or modify
dnl   it under the terms of the GNU General Public License version 2 as
dnl   published by the Free Software Foundation.
dnl
dnl   This program is distributed in the hope that it will be useful,
dnl   but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl   GNU General Public License for more details.
dnl
dnl   You should have received a copy of the GNU General Public
dnl   License along with this program; if not, write to the Free Software
dnl   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
dnl

AC_INIT(hpiinfo,m4_esyscmd(cat PACKAGE_VERSION))
AM_INIT_AUTOMAKE
AC_SUBST(RPM_RELEASE,1)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

#
# Some Fully Resolved Install Paths
# (for the packaging system and friends)
#
if test ${prefix} = "NONE" ; then
  AC_SUBST(LOCAL_PREFIX,/usr/local)
else
  AC_SUBST(LOCAL_PREFIX,${prefix})
fi

#
# Basic Compiler Checks
#
AC_PROG_CXX
AC_LANG(C++)

#
# Check for Qt (Mandatory)
#
PKG_CHECK_MODULES(QT5,Qt5Core Qt5Widgets Qt5Gui Qt5Network,,[AC_MSG_ERROR([*** Qt5 not found ***])])
AC_CHECK_PROG(MOC_NAME,moc-qt5,[moc-qt5],[moc])
AC_SUBST(QT_MOC,$MOC_NAME)

AC_CHECK_PROG(LUPDATE_NAME,lupdate-qt5,[lupdate-qt5],[lupdate])
AC_SUBST(QT_LUPDATE,$LUPDATE_NAME)

AC_CHECK_PROG(LRELEASE_NAME,lrelease-qt5,[lrelease-qt5],[lrelease])
AC_SUBST(QT_LRELEASE,$LRELEASE_NAME)


#PKG_CHECK_MODULES(QT4,QtGui QtCore QtNetwork,[],[AC_MSG_ERROR([*** Qt4 not found ***])])
#AC_CHECK_PROG(MOC_NAME,moc-qt4,[moc-qt4],[moc])
#AC_SUBST(MOC,$MOC_NAME)

#
# Check for AudioScience HPI
#
AC_CHECK_HEADER(asihpi/hpi.h,[],[AC_ERROR([*** HPI not found ***])])

#
# Determine the target architecture
#
AR_GCC_TARGET()
AC_SUBST(VENDOR,$ar_gcc_distro)
AC_SUBST(ARCH,$ar_gcc_arch)

#
# Determine Distro
#
AR_GET_DISTRO()
AC_SUBST(DISTRO,$ar_gcc_distro)
case "$ar_distro_id" in
     debian|linuxmint|ubuntu)
       AC_MSG_NOTICE([Distro is Debian-ish])
       DISTRO_IS_DEBIANISH=yes
       AC_SUBST(USERMODE_PKG,"")
       AC_SUBST(HAVE_USERMODE,"yes")
       AC_SUBST(HPIINFO_DESKTOP_FILE,"hpiinfo-sudo.desktop")
     ;;

     centos|rhel|fedora|rocky)
       AC_MSG_NOTICE([Distro is RedHat-ish])
       AC_SUBST(USERMODE_PKG,"usermode usermode-gtk")
       AC_SUBST(HAVE_USERMODE,"yes")
       AC_SUBST(HPIINFO_DESKTOP_FILE,"hpiinfo-root.desktop")
     ;;

     *)
       AC_MSG_NOTICE([Distro is unknown])
       AC_SUBST(USERMODE_PKG,"")
       AC_SUBST(HAVE_USERMODE,"no")
       AC_SUBST(HPIINFO_DESKTOP_FILE,"hpiinfo.desktop")
     ;;
esac

#
# Configure RPM Build
#
AC_CHECK_PROG(RPMBUILD_FOUND,rpmbuild,[yes],[])
if test -z $RPMBUILD_FOUND ; then
  AC_SUBST(RPMBUILD,rpm)
else
  AC_SUBST(RPMBUILD,rpmbuild)
fi
if test -d /usr/src/redhat ; then
  AC_SUBST(RPM_ROOT,/usr/src/redhat)
  AC_SUBST(VENDOR,redhat)
else
  AC_SUBST(RPM_ROOT,/usr/src/packages)
  AC_SUBST(VENDOR,suse)
fi 

AC_CONFIG_FILES([ \
    debian/source/Makefile \
    debian/Makefile \
    icons/Makefile \
    src/Makefile \
    xdg/Makefile \
    xdg/install_usermode.sh \
    hpiinfo.spec \
    build_debs.sh \
    Makefile ])
AC_OUTPUT()
chmod 755 build_debs.sh
chmod 755 xdg/install_usermode.sh

AC_MSG_NOTICE()
AC_MSG_NOTICE(Now enter 'make' to build the software.)
AC_MSG_NOTICE()
