#ifndef CLN_PARSER_H
#define CLN_PARSER_H

#include "syntax.h"

struct syntax_tree *parse(void);
struct syntax_tree *parse_string(const char *s);

#endif
