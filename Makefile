CFLAGS=-w
.PHONY: all
all: compiler

parse: parse.o err.o parser.o str.o syntax.o

interp: interp.o err.o parser.o str.o syntax.o value.o

compiler: compiler.o err.o str.o value.o

compiler.o: caleinrtl.inc.c

compiler.c: compiler.cln interp
	./interp compiler.cln < compiler.cln > compiler.c
