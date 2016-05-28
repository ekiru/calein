#!/bin/bash

./interp compiler.cln < "$1" > /tmp/calein-script.c &&
cc -I . -o /tmp/calein-exe /tmp/calein-script.c err.c str.c value.c &&
/tmp/calein-exe
