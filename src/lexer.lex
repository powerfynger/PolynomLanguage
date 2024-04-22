%{
    #include "parser.tab.h"
%}

%option yylineno
%option noyywrap

%%

[0-9]+          { 
                yylval = atoi(yytext);
                return NUM;
                }
[ \t\r\n]      ; // whitespace
[;]            { return EOF; }
[a-zA-Z]       { 
                 yylval =  *yytext;
                 return LETTER; 
               }
.              { return *yytext; }

%%