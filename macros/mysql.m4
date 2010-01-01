dnl 
dnl   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
dnl 
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

# Configure paths for mysql

AC_DEFUN([GAE_PATH_MYSQL],
[dnl 
dnl Get the cflags and libraries
dnl
AC_ARG_WITH(mysql,[  --with-mysql=PFX        prefix where libmsql is installed (optional)], mysql_prefix="$withval", mysql_prefix="")
AC_ARG_WITH(mysql-libraries,[  --with-mysql-libraries=DIR   directory where mysql library is installed (optional)], mysql_libraries="$withval", mysql_libraries="")
AC_ARG_WITH(mysql-includes,[  --with-mysql-includes=DIR    directory where mysql header files are installed (optional)], mysql_includes="$withval", mysql_includes="")
dnl AC_ARG_ENABLE(mysqltest, [  --disable-mysqltest       Do not try to compile and run a test mysql program],, enable_mysqltest=yes)

  if test "x$mysql_libraries" != "x" ; then
    MYSQL_LIBS="-L$mysql_libraries"
  elif test "x$mysql_prefix" != "x" ; then
    MYSQL_LIBS="-L$mysql_prefix/lib"
  elif test "x$prefix" != "xNONE" ; then
    MYSQL_LIBS="-L$libdir"
  fi

dnl   if test "x$mysql_includes" != "x" ; then
dnl     MYSQL_CFLAGS="-I$mysql_includes"
dnl   elif test "x$mysql_prefix" != "x" ; then
dnl     MYSQL_CFLAGS="-I$mysql_prefix/include"
dnl   elif test "$prefix" != "xNONE"; then
dnl     MYSQL_CFLAGS="-I$prefix/include"
dnl   fi

  AC_MSG_CHECKING(for MySQL headers)
  no_mysql=""

  if test "x$MYSQL_CFLAGS" = "x" ; then
    MYSQL_CFLAGS=`mysql_config --cflags`
    AC_MSG_RESULT($MYSQL_CFLAGS)
  fi

  AC_MSG_CHECKING(for MySQL library)
  dnl if test x"$MYSQL_LIBS" = "x" ; then
   dnl For some odd reason, this fails on when building a deb package
    MYSQL_LIBS=`mysql_config --libs`
dnl     found=`echo $MYSQL_LIBS | grep mysqlclient`
dnl     for i in /usr/local /opt /usr/local/apache /usr; do
dnl 	if test -e $i/lib/mysql/libmysqlclient.a -o $i/lib/mysql/libmysqlclient.so; then
dnl 	    MYSQL_LIBS="-L$i/lib/mysql -lmysqlclient -lcrypt -lnsl -lm -lz"
dnl 	    break;
dnl 	fi
dnl     done
    AC_MSG_RESULT($MYSQL_LIBS)
  dnl fi

AC_DEFINE(HAVE_MYSQL, 1, [Mysql package])
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(MYSQL_LIBS)
])
