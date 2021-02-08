## Process this file with automake to produce Makefile.in
# $Id: Makefile.am,v 1.6 2001/02/27 12:22:09 leydold Exp $

info_TEXINFOS = prng.texi

prng_TEXINFOS = \
 tables.texi \
 theory.texi \
 usage.texi

noinst_DATA = 

EXTRA_DIST = \
 mdate-sh \
 prng.html \
 prng.txt \
 prng.dvi \
 prng.ps \
 prng.pdf \
 texinfo.tex

SUFFIXES = .texi .html .txt

# make html file ...
.texi.html:
	makeinfo --html $< -o $@

# make plain text file ...
.texi.txt:
	makeinfo --no-headers --number-sections $< -o $@

# make pdf file ...
.texi.pdf:
	texi2pdf $<

# .texi.pdf seems not to work. try it with this construction
prng.pdf:  prng.info prng.texi version.texi $(prng_TEXINFOS)
	texi2pdf prng.texi

# clean backup files
CLEANFILES = *~

# clean generated files
MAINTAINERCLEANFILES = \
 Makefile.in \
 prng.html \
 prng.txt \
 prng.pdf

