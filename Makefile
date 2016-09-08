CFLAGS=-w
.PHONY: all copy-stage0 check
all: compiler

parse: parse.o err.o parser.o str.o syntax.o

compiler: compiler.o err.o str.o value.o

compiler.o: caleinrtl.inc.c

compiler.c: compiler.cln stage0 codegen.cln parser.cln prelude.cln
	./stage0 compiler.cln > compiler.c

stage0: stage0.c err.o str.o value.o

copy-stage0:
	cat caleinrtl.inc.c > stage0.c && sed 1d compiler.c >> stage0.c

check: test.cln compiler compile.sh
	prove -e ./compile.sh t
