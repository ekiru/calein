#!/bin/bash

cflags='-w -I .'
executer=

if [ $1 = '-g' ]
then
	shift
	cflags="$cflags -g"
	executer=lldb
fi

#./interp compiler.cln < "$1" > /tmp/calein-script.c &&
./compiler < "$1" > /tmp/calein-script.c &&
cc $cflags -o /tmp/calein-exe /tmp/calein-script.c err.c str.c value.c &&
$executer /tmp/calein-exe
