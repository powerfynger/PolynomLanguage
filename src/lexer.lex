%{
    #include "parser.tab.h"


%}

%option yylineno
%option noyywrap


%%

[0-9]+         {
                
                yylval = atoi(yytext);
                
                return NUM;
              }
[ \t\r\n]      ; // whitespace
[;]            { return EOF; }
[a-z]         { 
                 yylval =  *yytext;
                 return LETTER; 
               }
[A-Z]         { 
                 yylval =  *yytext;
                 return VAR; 
               }
"#".* { 
                yylineno++;
                }

.              { return *yytext; }

%%