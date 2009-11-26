dnl  
dnl  Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
dnl  
dnl  This program is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU General Public License as published by
dnl  the Free Software Foundation; either version 3 of the License, or
dnl  (at your option) any later version.
dnl  
dnl  This program is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl  GNU General Public License for more details.
dnl  You should have received a copy of the GNU General Public License
dnl  along with this program; if not, write to the Free Software
dnl  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
dnl  

AC_PATH_PROG(PHP_CONFIG, php-config)

if test X"$PHP_CONFIG" != "x" ; then
  PHP_INCLUDES=`$PHP_CONFIG --includes 2>/dev/null`
  EXTENSION_DIR=`$PHP_CONFIG --extension-dir`
  php_prefix=`$PHP_CONFIG --prefix 2>/dev/null`
fi

if test -z "$php_prefix"; then
  AC_MSG_ERROR(Cannot find php-config. Please use --with-php-config=PATH)
fi

AC_MSG_CHECKING(for PHP prefix)
AC_MSG_RESULT($php_prefix)

AC_MSG_CHECKING(for PHP extension directory)
AC_MSG_RESULT($EXTENSION_DIR)

dnl

AC_ARG_ENABLE(phpgnuae,
  AC_HELP_STRING([--enable-php], [whether to enable PHP support]),
  [case "${enableval}" in
    yes) phpgnuae=yes ;;
    no)  phpgnuae=no ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for enable-php option]) ;;
  esac], phpgnuae=yes
)
AM_CONDITIONAL(ENABLE_PHP_GNUAE, [test x"$phpgnuae" = xyes])
if test x$phpgnuae = xyes; then
    AC_DEFINE(ENABLE_PHP_GNUAE, [1], [Enable PHP support for GnuAE])
fi

dnl if test "x$phpgnuae" = x"yes"; then
dnl   PHP_ADD_INCLUDE(/home/rob/projects/gnu/gnuae/src)
dnl   PHP_ADD_LIBRARY_WITH_PATH(gnuaec, /usr/local/lib)
dnl   AC_DEFINE(HAVE_GNUAE, 1, [Whether you have the GnuAE library])
dnl   PHP_NEW_EXTENSION(gnuae, wrapper.c NEC.cc, $ext_shared)
dnl dnl  PHP_NEW_EXTENSION(gnuae, wrapper.c ../src/NEC.cc, $ext_shared,, -lgnuaec)
dnl fi


AC_SUBST(EXTENSION_DIR)
AC_SUBST(php_prefix)
AC_SUBST(PHP_INCLUDES)
