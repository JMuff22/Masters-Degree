## Process this file with automake to produce Makefile.in
## $Id: Makefile.am,v 1.4 2001/02/27 12:22:09 leydold Exp $

LDADD = $(top_builddir)/src/libprng.a -lm

INCLUDES = \
 -I$(top_builddir) \
 -I$(top_srcdir)/src

check_PROGRAMS = \
 validate

TESTS = \
 validate

EXTRA_DIST = \
 iter.c \
 tests.dat

iter: iter.c $(top_srcdir)/src/support.c $(top_srcdir)/src/prng.h
	$(CC) $(CFLAGS) $(AM_CFLAGS) $(INCLUDES) $(CPPFLAGS) -o iter -DITER_COUNT $(top_srcdir)/src/support.c iter.c

# clean backup files
CLEANFILES = iter *~

