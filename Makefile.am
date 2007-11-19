EXTRA_DIST = autogen.sh sollya.h libsollyaexample.c compile.sh expansion.c expansion.h externalfun.c externalproc.c doc/sollya.pdf

AM_YFLAGS = -d
AM_LFLAGS = -o$(LEX_OUTPUT_ROOT).c

BUILT_SOURCES = \
miniparser.h \
parser.h \
internparser.h \
lexer.c \
minilexer.c \
internlexer.c 

bin_PROGRAMS = sollya
sollya_SOURCES = \
internparser.y \
miniparser.y \
parser.y \
internlexer.l \
lexer.l \
minilexer.l \
help.h \
assignment.c \
assignment.h \
chain.c \
chain.h \
double.c \
double.h \
execute.c \
execute.h \
expression.c \
expression.h \
external.c \
external.h \
fpminimax.c \
fpminimax.h \
general.c \
general.h \
implement.c \
implement.h \
infnorm.c \
infnorm.h \
integral.c \
integral.h \
library.c \
library.h \
main.c \
main.h \
pari_utils.c \
pari_utils.h \
plot.c \
plot.h \
proof.c \
proof.h \
remez.c \
remez.h \
taylor.c \
taylor.h \
worstcase.c \
worstcase.h \
xml.c \
xml.h 
sollya_CFLAGS = $(AM_CFLAGS)

include_HEADERS = sollya.h

lib_LTLIBRARIES     = libsollya.la
libsollya_la_SOURCES = \
sollya.h \
internparser.y \
miniparser.y \
parser.y \
internlexer.l \
lexer.l \
minilexer.l \
help.h \
assignment.c \
assignment.h \
chain.c \
chain.h \
double.c \
double.h \
execute.c \
execute.h \
expression.c \
expression.h \
external.c \
external.h \
fpminimax.c \
fpminimax.h \
general.c \
general.h \
implement.c \
implement.h \
infnorm.c \
infnorm.h \
integral.c \
integral.h \
library.c \
library.h \
pari_utils.c \
pari_utils.h \
plot.c \
plot.h \
proof.c \
proof.h \
remez.c \
remez.h \
taylor.c \
taylor.h \
worstcase.c \
worstcase.h \
xml.c \
xml.h 


LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

