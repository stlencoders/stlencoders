# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = stlencode stldecode

noinst_PROGRAMS = stlbench

noinst_HEADERS = getopt.hpp

stlencode_SOURCES = stlencode.cpp

stldecode_SOURCES = stldecode.cpp

stlbench_SOURCES = stlbench.cpp

check_SCRIPTS = check.sh

dist_check_SCRIPTS = $(check_SCRIPTS)

TESTS_ENVIRONMENT = $(SHELL) -e

TESTS = $(check_SCRIPTS)

EXTRA_DIST = stlencode.vcxproj stldecode.vcxproj stlbench.vcxproj

CLEANFILES = *.gcda *.gcno *.gcov
