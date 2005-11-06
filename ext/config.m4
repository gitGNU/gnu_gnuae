PHP_ARG_ENABLE(gnuae, whether to enable GnuAE support,
[ --enable-gnuae   Enable GnuAE support])

if test "$PHP_GNUAE" = "yes"; then
  PHP_ADD_INCLUDE(/home/rob/projects/gnu/gnuae/src)

  PHP_ADD_LIBRARY_WITH_PATH(gnuaec, /usr/local/lib)
  AC_DEFINE(HAVE_GNUAE, 1, [Whether you have the GnuAE library])
  PHP_NEW_EXTENSION(gnuae, wrapper.c NEC.cc, $ext_shared)
dnl  PHP_NEW_EXTENSION(gnuae, wrapper.c ../src/NEC.cc, $ext_shared,, -lgnuaec)
fi

