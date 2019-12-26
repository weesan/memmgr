#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(memmgr, 1.0.0, weesan@weesan.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([include/memmgr.h])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(pthread, main)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

AC_CONFIG_FILES([
    Makefile
    include/Makefile
    test/Makefile
])

AC_OUTPUT
