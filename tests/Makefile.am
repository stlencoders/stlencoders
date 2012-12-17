# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_HEADERS = util.hpp xassert.hpp

check_PROGRAMS = \
	test_base2 test_base16 test_base32 test_base64 \
	test_lookup test_traits

test_base2_SOURCES = test_base2.cpp test_base2.hpp

test_base16_SOURCES = test_base16.cpp test_base16.hpp

test_base32_SOURCES = test_base32.cpp test_base32.hpp

test_base64_SOURCES = test_base64.cpp test_base64.hpp

test_lookup_SOURCES = test_lookup.cpp test_lookup.hpp

test_traits_SOURCES = test_traits.cpp test_traits.hpp

TESTS = $(check_PROGRAMS)

EXTRA_DIST = vcxtests.cpp tests.vcxproj

CLEANFILES = *.gcda *.gcno *.gcov
