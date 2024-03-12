%{
    #include "parser.tab.h"
%}

%option yylineno
%option noyywrap

%%

[0-9]+          { yylval = atoi(yytext);
                  return NUM;
                }
[ \t\r\n]      ; // whitespace
[e]            {return EOF;}
[xX]           {return 'x';  }
.              { return *yytext; }

%%