AC_DEFUN([GAE_AC_PATH_DEJAGNU], [
dirlist=".. ../../ ../../../ ../../../../ ../../../../../ ../../../../../../ ../
../../../../../.. ../../../../../../../.. ../../../../../../../../.. ../../../..
/../../../../../.."
AC_MSG_CHECKING(for the DejaGnu header file)

dnl Look for DejaGnu support
AC_ARG_ENABLE(dejagnu, [  --enable-dejagnu          Enable support for DejaGnu],
[case "${enableval}" in
  yes) dejagnu=yes ;;
  no)  dejagnu=no ;;
  *)   AC_MSG_ERROR([bad value ${enableval} for enable-dejagnu option]) ;;
esac])

dnl FIXME: force DejaGnu support for now
dejagnu=yes
AM_CONDITIONAL(HAVE_DEJAGNU, test x$dejagnu = xyes)

AC_ARG_WITH(dejagnu, [  --with-dejagnu       directory where DejaGnu header
s are], with_dejagnu=${withval})
AC_CACHE_VAL(ac_cv_path_dejagnu,[

if test x"${with_dejagnu}" != x ; then
  if test -f ${with_dejagnu}/dejagnu.h ; then
    ac_cv_path_dejagnu=`(cd ${with_dejagnu}; pwd)`
  elif test -f ${with_dejagnu}/libdejagnu/dejagnu.h ; then
    ac_cv_path_dejagnu=`(cd ${with_dejagnu}/libdejagnu; pwd)`
  else
    AC_MSG_ERROR([${with_dejagnu} directory doesn't contain dejagnu.h])
  fi
else
  for i in $dirlist /usr/local/include /usr/include /opt/include ; do
    if test -f $i/dejagnu.h; then
      ac_cv_path_dejagnu=`(cd $i; pwd)`
      break
    fi
  done
fi
])

if test "x${ac_cv_path_dejagnu}" != "xno"; then
  DEJAGNU_PATH="-I${ac_cv_path_dejagnu}"
  AC_MSG_RESULT(${ac_cv_path_dejagnu})
else
  DEJAGNU_PATH= ""
  AC_MSG_RESULT(none)
fi

AC_SUBST(DEJAGNU_PATH)
])

AC_DEFUN([GAE_AC_PATH_TCLSH], [
dirlist=".. ../../ ../../../ ../../../../ ../../../../../ ../../../../../../ ../
../../../../../.. ../../../../../../../.. ../../../../../../../../.. ../../../..
/../../../../../.."
no_itcl=true
AC_MSG_CHECKING(for the tclsh program)
AC_ARG_WITH(tclinclude, [  --with-tclinclude       directory where tcl header
s are], with_tclinclude=${withval})
AC_CACHE_VAL(ac_cv_path_tclsh,[
dnl first check to see if --with-itclinclude was specified
if test x"${with_tclinclude}" != x ; then
  if test -f ${with_tclinclude}/tclsh ; then
    ac_cv_path_tclsh=`(cd ${with_tclinclude}; pwd)`
  elif test -f ${with_tclinclude}/src/tclsh ; then
    ac_cv_path_tclsh=`(cd ${with_tclinclude}/src; pwd)`
  else
    AC_MSG_ERROR([${with_tclinclude} directory doesn't contain tclsh])
  fi
fi
])

dnl next check in private source directory
dnl since ls returns lowest version numbers first, reverse its output
if test x"${ac_cv_path_tclsh}" = x ; then
    dnl find the top level Itcl source directory
    for i in $dirlist; do
        if test -n "`ls -dr $srcdir/$i/tcl* 2>/dev/null`" ; then
            tclpath=$srcdir/$i
            break
        fi
    done

    dnl find the exact Itcl source dir. We do it this way, cause there
    dnl might be multiple version of Itcl, and we want the most recent one.
    for i in `ls -dr $tclpath/tcl* 2>/dev/null ` ; do
        if test -f $i/src/tclsh ; then
          ac_cv_path_tclsh=`(cd $i/src; pwd)`/tclsh
          break
        fi
    done
fi

dnl see if one is installed
if test x"${ac_cv_path_tclsh}" = x ; then
   AC_MSG_RESULT(none)
   AC_PATH_PROG(tclsh, tclsh)
else
   AC_MSG_RESULT(${ac_cv_path_tclsh})
fi
TCLSH="${ac_cv_path_tclsh}"
AC_SUBST(TCLSH)
])


AC_DEFUN([GAE_AC_PATH_DOCBOOK], [
dirlist=".. ../../ ../../.. ../../../.. ../../../../.. ../../../../../.. ../../../../../../.. ../../../../../../../.. ../../../../../../../../.. ../../../../../../../../../.."
AC_MSG_CHECKING(for docbook tools)
AC_ARG_WITH(oskith, [  --with-docbook       directory where the db2 sgml tools are], with_docbook=${withval})
AC_CACHE_VAL(ac_cv_c_docbook,[
dnl first check to see if --with-docbook was specified
if test x"${with_docbook}" != x ; then
  if test -f ${with_docbook}/db2html ; then
    ac_cv_c_docbook=`(cd ${with_docbook}; pwd)`
  else
    AC_MSG_ERROR([${with_docbook} directory doesn't contain SGML tools])
  fi
fi
])
if test x"${ac_cv_c_docbook}" = x ; then
    for i in $ac_default_prefix/bin /usr/local/bin $OSKITHDIR/../bin /usr/bin /bin /opt /home; do
	dnl See is we have an SGML tool in that directory.
	if test -f $i/db2html ; then
	    ac_cv_c_docbook=$i
	    break
	fi
    done
fi

if test x"${ac_cv_c_docbook}" = x ; then
    AC_MSG_RESULT(none)
else
    DOCBOOK="${ac_cv_c_docbook}"
    AC_MSG_RESULT(${ac_cv_c_docbook})
fi

AC_SUBST(DOCBOOK)
])


AC_DEFUN([GAE_AC_PATH_ABELMON], [
dirlist=".. ../../ ../../../ ../../../../ ../../../../../ ../../../../../../ ../
../../../../../.. ../../../../../../../.. ../../../../../../../../.. ../../../..
/../../../../../.."
AC_MSG_CHECKING(for the Abelmon header file)

dnl Look for Abelmon support
AC_ARG_ENABLE(abelmon, [  --enable-abelmon          Enable support for Abelmon],
[case "${enableval}" in
  yes) abelmon=yes ;;
  no)  abelmon=no ;;
  *)   AC_MSG_ERROR([bad value ${enableval} for enable-abelmon option]) ;;
esac])

AC_ARG_WITH(abelmon, [  --with-abelmon-include       directory where Abelmon header
s are], with_abelmon_include=${withval})
AC_CACHE_VAL(ac_cv_path_abelh,[

if test x"${with_abelmon_include}" != x ; then
  if test -f ${with_abelmon_include}/abelmon.h ; then
    ac_cv_path_abelh=`(cd ${with_abelmon_include}; pwd)`
  elif test -f ${with_abelmon_include}/libabelmon/abelmon.h ; then
    ac_cv_path_abelh=`(cd ${with_abelmon_include}/libabelmon; pwd)`
  else
    AC_MSG_ERROR([${with_abelmon_include} directory doesn't contain abelmon.h])
  fi
else
  dnl Look in the top level source directory
  echo "${srcdir}/../abelmon/src/abelmon.h"
  if test -f ${srcdir}/../abelmon/src/abelmon.h; then
    ac_cv_path_abelh=`(cd ${srcdir}/../abelmon; pwd)`
  else
    for i in /usr/local /usr /opt /home/latest; do
      if test -f $i/include/abelmon.h; then
        ac_cv_path_abelh=`(cd $i/include; pwd)`
        break
      fi
    done
  fi
fi
])

if test "x${ac_cv_path_abelh}" != "xno"; then
  ABELINCL="${ac_cv_path_abelh}"
  AC_MSG_RESULT(${ac_cv_path_abelh})
else
  ABELINCL= ""
  AC_MSG_RESULT(none)
fi
AC_SUBST(ABELINCL)

AC_ARG_WITH(abelmon, [  --with-abelmon-lib       directory where the Abelmon library is], with_abelmon_lib=${withval})
AC_CACHE_VAL(ac_cv_path_abellib,[

if test x"${with_abelmon_include}" != x ; then
  if test -f ${with_abelmon_include}/abelmon.h ; then
    ac_cv_path_abellib=`(cd ${with_abelmon_include}; pwd)`
  elif test -f ${with_abelmon_lib}/abelmon/libabel.la ; then
    ac_cv_path_abellib=`(cd ${with_abelmon_lib}/libabel.la; pwd)`
  else
    AC_MSG_ERROR([${with_abelmon_lib} directory doesn't contain libabel.la])
  fi
else
  dnl Look in our build tree for a fresh version
  for i in $dirlist; do
    if test -f $i/abelmon/libabel/libabel.la; then
      ac_cv_path_abellib=`(cd $i/abelmon/libabel; pwd)`
      break
    fi
  done
  dnl no build found, look in the standard install location
  if test "x${ac_cv_path_abellib}" = "x"; then
    for i in ${prefix}/usr/local /usr /opt /home/latest; do
      if test -f $i/lib/libabel.la; then
        ac_cv_path_abellib=`(cd $i/abelmon/lib; pwd)`
        break
      fi
    done
  fi
fi
])

if test "x${ac_cv_path_abellib}" != "xno"; then
  ABELLIB="${ac_cv_path_abellib}"
  AC_MSG_RESULT(${ac_cv_path_abellib})
else
  ABELLIB= ""
  AC_MSG_RESULT(none)
fi

AC_SUBST(ABELLIB)

])


