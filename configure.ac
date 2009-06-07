#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.60)
AC_INIT([sollya], [1.1.3], [christoph.lauter@ens-lyon.org, sylvain.chevillard@ens-lyon.org, mioara.joldes@ens-lyon.fr])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([1.6 no-define dist-zip dist-bzip2])


# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AC_PROG_CXX 
AM_PROG_CC_C_O
AC_PROG_LEX
if test "$LEX" != flex; then
  LEX="$SHELL $missing_dir/missing flex"
  AC_SUBST(LEX_OUTPUT_ROOT, lex.yy)
  AC_SUBST(LEXLIB, '')
fi
AC_LIBTOOL_DLOPEN
AC_DISABLE_SHARED
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_CONFIG_MACRO_DIR([m4])

#Check whether flex and bison support interactive and pure parsers

AC_ARG_ENABLE(strict-lexer-parser-check, [  --enable-strict-lexer-parser-check enables strict compatibility checking for building the lexer and parser files], [STRICTFLEXBISONTESTING="1"], [STRICTFLEXBISONTESTING=""])

AC_MSG_CHECKING([flex supports interactive and pure lexers])
if test `echo -e "%{\n%}\n\n%option always-interactive\n%option reentrant\n%option prefix=\"coucou\"\n%option bison-bridge\n%option nounput\n\n%%\n"test" { }\n%%\n" > conftest.l ; $LEX conftest.l > /dev/null 2> /dev/null ; echo $?; rm -f lex.coucou.c` -eq 0 ; then 
AC_MSG_RESULT(yes)
else
if test "x$STRICTFLEXBISONTESTING" = "x"; then
   AC_MSG_RESULT(flex version unable to compile the lexer from the grammar files)
else
   AC_MSG_ERROR(no)	
fi
fi

AC_MSG_CHECKING([bison supports interactive and pure parsers])
if test `echo -e "%{\n#define YYERROR_VERBOSE 1\n#define YYPARSE_PARAM scanner\n#define YYLEX_PARAM scanner\n%}\n\n%defines\n%pure_parser\n\n%%\nstart: \".\"\n{ }\n;\n\n" > conftest.y ; $YACC conftest.y > /dev/null 2> /dev/null ; echo $?; rm -f y.tab.*` -eq 0 ; then 
AC_MSG_RESULT(yes)
else
if test "x$STRICTFLEXBISONTESTING" = "x"; then
   AC_MSG_RESULT(bison version unable to compile the parser from the grammar files)
else
   AC_MSG_ERROR(no)	
fi
fi

# withs...

AC_ARG_WITH(gmp-include,
   [  --with-gmp-include=DIR  GMP include directory ],
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval")
AC_ARG_WITH(gmp-lib,
   [  --with-gmp-lib=DIR      GMP lib directory ], [
   AM_LDFLAGS="$AM_LDFLAGS -L$withval"
  ])
AC_ARG_WITH(gmp,
   [  --with-gmp=DIR          GMP install directory ], [
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval/include"
   AM_LDFLAGS="$AM_LDFLAGS -L$withval/lib"
  ])

AC_ARG_WITH(mpfr-include,
   [  --with-mpfr-include=DIR  MPFR include directory ],
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval")
AC_ARG_WITH(mpfr-lib,
   [  --with-mpfr-lib=DIR      MPFR lib directory ], [
   AM_LDFLAGS="$AM_LDFLAGS -L$withval"
  ])
AC_ARG_WITH(mpfr,
   [  --with-mpfr=DIR          MPFR install directory ], [
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval/include"
   AM_LDFLAGS="$AM_LDFLAGS -L$withval/lib"
  ])

AC_ARG_WITH(fplll-include,
   [  --with-fplll-include=DIR  fplll include directory ],
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval")
AC_ARG_WITH(fplll-lib,
   [  --with-fplll-lib=DIR      fplll lib directory ], [
   AM_LDFLAGS="$AM_LDFLAGS -L$withval"
  ])
AC_ARG_WITH(fplll,
   [  --with-fplll=DIR          fplll install directory ], [
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval/include"
   AM_LDFLAGS="$AM_LDFLAGS -L$withval/lib"
  ])


XML2INCLUDEGIVEN=""
XML2LIBGIVEN=""
AC_ARG_WITH(xml2-include,
   [  --with-xml2-include=DIR  XML2 include directory ],[
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval"
   XML2INCLUDEGIVEN=1
   ])
AC_ARG_WITH(xml2-lib,
   [  --with-xml2-lib=DIR      XML2 lib directory ], [
   AM_LDFLAGS="$AM_LDFLAGS -L$withval"
   XML2LIBGIVEN=1
  ])
AC_ARG_WITH(xml2,
   [  --with-xml2=DIR          XML2 install directory ], [
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval/include"
   AM_LDFLAGS="$AM_LDFLAGS -L$withval/lib"
   XML2INCLUDEGIVEN=1
   XML2LIBGIVEN=1
  ])

AC_ARG_WITH(mpfi-include,
   [  --with-mpfi-include=DIR  MPFI include directory ],
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval")
AC_ARG_WITH(mpfi-lib,
   [  --with-mpfi-lib=DIR      MPFI lib directory ], [
   AM_LDFLAGS="$AM_LDFLAGS -L$withval"
  ])
AC_ARG_WITH(mpfi,
   [  --with-mpfi=DIR          MPFI install directory ], [
   AM_CPPFLAGS="$AM_CPPFLAGS -I$withval/include"
   AM_LDFLAGS="$AM_LDFLAGS -L$withval/lib"
  ])


#Add xml2 include and lib

AC_CHECK_PROG(XML2CONFIG,xml2-config,[xml2-config],[false])

if test "x$XML2INCLUDEGIVEN" = "x"; then
  AM_CPPFLAGS="$AM_CPPFLAGS "`$XML2CONFIG --cflags`
fi

if test "x$XML2LIBGIVEN" = "x"; then
  XML2LIBS=`$XML2CONFIG --libs`
  AC_SEARCH_LIBS([xmlTextReaderIsEmptyElement], [$XML2LIBS])
fi


# Save user flags

OLDCFLAGS="$CFLAGS"
OLDCPPFLAGS="$CPPFLAGS"
OLDLDFLAGS="$LDFLAGS"

# Checks for libraries.

CPPFLAGS="$AM_CPPFLAGS $CPPFLAGS"
LDFLAGS="$AM_LDFLAGS $LDFLAGS"

dlopen_ok="yes"
AC_CHECK_LIB([c], [dlopen], [], [dlopen_ok="no"])
if [[ $dlopen_ok == "no" ]] ; then
  AC_CHECK_LIB([dl], [dlopen], [], AC_MSG_ERROR([libdl unusable]))
fi
AC_CHECK_LIB([gmp], [__gmpz_init], [], AC_MSG_ERROR([libgmp unusable]))
AC_CHECK_LIB([gmp], [__gmpz_fac_ui], [], AC_MSG_ERROR([libgmp version too old]))
AC_CHECK_LIB([gmp], [__gmpz_bin_uiui], [], AC_MSG_ERROR([libgmp version too old]))
AC_CHECK_LIB([gmp], [__gmpz_export], [], AC_MSG_ERROR([libgmp version too old]))
AC_CHECK_LIB([mpfr], [mpfr_init], [], AC_MSG_ERROR([libmpfr unusable]))
AC_CHECK_LIB([mpfr], [mpfr_erfc], [], AC_MSG_ERROR([libmpfr version too old]))
AC_CHECK_LIB([xml2], [xmlTextReaderIsEmptyElement], [], AC_MSG_ERROR([libxml2 unusable]))
AC_CHECK_LIB([mpfi], [mpfi_init], [], AC_MSG_ERROR([libmpfi unusable]))

#Special check for fplll
AC_LANG_PUSH([C++])
AC_MSG_CHECKING([for fplll support])
AC_RUN_IFELSE([AC_LANG_PROGRAM([[#include <stdlib.h>]]
[[#include <fplll.h>]] 
[[#include <gmp.h>]]
, [[ZZ_mat<mpz_t> * M; M = new ZZ_mat<mpz_t>(3,3); if(M!=NULL) exit(0); else exit(1);]])],
[AC_MSG_RESULT(yes) 
],[AC_MSG_ERROR([fplll unusable (or g++ too new -- see README)])
])
AC_LANG_POP([C++])	

#Check for -Wl,-export-dynamic etc.

CPPFLAGS="$OLDCPPFLAGS"
CFLAGS="$OLDCFLAGS -fPIC"
LDFLAGS="$OLDLDFLAGS"


AC_MSG_CHECKING([for -fPIC support])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[]])],
[AC_MSG_RESULT(yes) 
AM_CFLAGS="$AM_CFLAGS -fPIC"
],[AC_MSG_RESULT(no)
])

CFLAGS="$OLDCFLAGS"
LDFLAGS="$OLDLDFLAGS -Wl,-export-dynamic"

AC_MSG_CHECKING([for -export-dynamic support])
AC_RUN_IFELSE([AC_LANG_PROGRAM([[#include <stdlib.h>]], [[exit(0);]])],
[AC_MSG_RESULT(yes) 
AM_LDFLAGS="$AM_LDFLAGS -Wl,-export-dynamic"
],[AC_MSG_RESULT(no)
])

LDFLAGS="$OLDLDFLAGS"

# Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdlib.h string.h sys/ioctl.h sys/time.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T


# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gettimeofday memset memmove strerror strtol backtrace])

AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_LDFLAGS)
AC_CONFIG_FILES([Makefile doc/Makefile tests/Makefile])
AC_OUTPUT
