#include "polynom.h"
#include "parser.tab.h"

int main() {
    yyparse();
    return 0;
}