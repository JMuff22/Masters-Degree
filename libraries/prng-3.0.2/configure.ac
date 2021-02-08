dnl Process this file with autoconf to produce a configure script.
dnl $Id: configure.in,v 1.9 2001/11/07 13:20:56 leydold Exp $

dnl Initialize.
AC_PREREQ(2.57)
AC_INIT([PRNG], [3.0.2], [prng@statistik.wu-wien.ac.at])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/prng.h])
AC_CONFIG_HEADER([config.h])

dnl Add dmalloc support.
AM_WITH_DMALLOC

dnl Check for which system.
AC_CANONICAL_HOST

dnl Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CPP
AC_CHECK_TOOL(RANLIB, ranlib, :)
AC_CHECK_TOOL(AR, ar, :)
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_PROG_LN_S

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_CHECK_SIZEOF(long long, 0)
AC_CHECK_SIZEOF(long, 0)

dnl Checks for header files
AC_HEADER_STDC
AC_CHECK_HEADERS(limits.h)

dnl Checks for libraries.

dnl Checks for library functions.
AC_CHECK_FUNCS(strtoul)

dnl Set flags for compiler
if test X"$GCC" = Xyes ; then
	AC_SUBST(AM_CFLAGS,"-Wall -fomit-frame-pointer")
fi

AC_CONFIG_FILES([\
        Makefile \
        src/Makefile \
        doc/Makefile \
        tests/Makefile \
        examples/Makefile ])
AC_OUTPUT

dnl -----------------------------------------




