#include <stdbool.h>

#include "err.h"
#include "parser.h"
#include "syntax.h"

int main() {
	bool parsed_one = false;
	for (;;) {
		struct syntax_tree *tree = parse();
		if (tree) {
			parsed_one = true;
			syntax_tree_display(tree);
		} else {
			break;
		}
	}	
	if (!parsed_one) {
		log_error("Couldn't parse a string.");
	}
}
