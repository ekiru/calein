#!/bin/bash

cflags='-w -I .'
executer=

if [ $1 = '-g' ]
then
	shift
	cflags="$cflags -g"
	executer=lldb
fi

if [ "$CALEIN_MEMDEBUG" -eq 1 ]
then
	cflags="$cflags -D CALEIN_REF_DEBUG"
fi

#./interp compiler.cln < "$1" > /tmp/calein-script.c &&
./compiler -g "$1" > /tmp/calein-script.c &&
cc $cflags -o /tmp/calein-exe /tmp/calein-script.c err.c str.c value.c &&
$executer /tmp/calein-exe
