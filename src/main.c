#include "polynom.h"
#include "parser.tab.h"

extern FILE* yyin;

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r"); 
    if (inputFile == NULL) 
    {
        fprintf(stderr, "Error: Unable to open file: %s.\n", argv[1]);
        return 1;
    }

    yyin = inputFile;
    yyparse();
    printf("\nEnd\n");
    return 0;
}