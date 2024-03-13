#include "polynom.h"
#include "parser.tab.h"

int main() {
    yyparse();
    printf("\nEnd\n");
    return 0;
}