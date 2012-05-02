# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_HEADERS = util.hpp

check_PROGRAMS = \
	test_lookup test_traits \
	test_base16 test_base32 test_base64

test_lookup_SOURCES = test_lookup.cpp

test_traits_SOURCES = test_traits.cpp

test_base16_SOURCES = test_base16.cpp

test_base32_SOURCES = test_base32.cpp

test_base64_SOURCES = test_base64.cpp

TESTS = $(check_PROGRAMS)

EXTRA_DIST = \
	portable.txt \
	test_lookup.vcxproj test_traits.vcxproj \
	test_base16.vcxproj test_base32.vcxproj test_base64.vcxproj
