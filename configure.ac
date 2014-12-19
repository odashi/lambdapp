#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([lambdapp], [0.1.0], [yus.takara@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/include/lambdapp/untyped.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_LANG([C++])
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_CC

# C++11 flags
CXXFLAGS="$CXXFLAGS -std=c++11"

# other compiler flags
CXXFLAGS="$CXXFLAGS -Wall"
CXXFLAGS="$CXXFLAGS -O2"

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/include/Makefile
    src/lib/Makefile
    src/test/Makefile
])

AC_CONFIG_MACRO_DIR([m4])

AC_OUTPUT
