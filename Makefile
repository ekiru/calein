.PHONY: all
all: parse interp

parse: parse.o err.o parser.o str.o syntax.o

interp: interp.o err.o parser.o str.o syntax.o
