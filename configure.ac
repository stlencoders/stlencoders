# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])

AC_INIT([stlencoders], [1.1.1], [tkemmer@computer.org])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
        Doxyfile
        Makefile
        include/Makefile
        src/Makefile
        tests/Makefile
])

AC_LANG([C++])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AC_CHECK_PROGS([DOXYGEN], [doxygen])

# check for system headers used by example programs
AC_CHECK_HEADERS([getopt.h unistd.h])

# check for stringencoders (used by stlbench)
AC_CHECK_HEADERS([modp_b2.h modp_b16.h modp_b64.h modp_b64w.h])
AC_CHECK_LIB([modpbase64], [main], [stlbench_LDADD="-lmodpbase64 $stlbench_LDADD"])

# check for apr-util (used by stlbench)
AC_CHECK_HEADERS([apr-1/apr_base64.h])
AC_CHECK_LIB([aprutil-1], [apr_base64_encode], [stlbench_LDADD="-laprutil-1 $stlbench_LDADD"])

# check for boost (used by stlbench)
AC_CHECK_HEADERS([boost/archive/iterators/base64_from_binary.hpp])
AC_CHECK_HEADERS([boost/archive/iterators/binary_from_base64.hpp])

# additional libs for stlbench
AC_SUBST([stlbench_LDADD])

# automake
AM_INIT_AUTOMAKE([-Wall -Werror])

# done
AC_OUTPUT
