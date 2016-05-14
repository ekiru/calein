#include "err.h"

#include <stdarg.h>
#include <stdio.h>

void log_error(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	putchar('\n');
}
