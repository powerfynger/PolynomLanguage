%{
    #include <stdio.h>
    #include <math.h>
    #include "polynom.h"
    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }
    

%}

%token NUM
%token LETTER
%token VAR
%define parse.error detailed
%left '+' '-' '*' 
%right '^'

%%


INPUT:
                |INPUT LINE
                ;
      

LINE:
                STATEMENT 
                | POLYNOM ';'
                ;

STATEMENT:    ':' POLYNOM ';'
                {
                  printPolynom((polynomMember*)$2);
                  printf("\n");
                }
                | EQUATION

POLYNOM:        FACTOR
                {
                  $$ = $1;
                  #ifdef DEBUG
                  printf("From factor to poly\n");
                  #endif
                }
                |  '-' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From -POLYNOM to POLYNOM\n");
                  #endif
                  multiplePolynomByFactor((polynomMember*)$2, -1);
                  $$ = $2;
                }
                /* | VAR
                {
                  #ifdef DEBUG
                  printf("=====From var to POLYNOM=====\n");
                  #endif
                  polynomMember* tmp = createPolynom(0, 0, 0);
                  summPolynom(tmp, getVariable($1));
                  $$ = tmp;
                } */
                | POLYNOM '^' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM ^ POLYNOM to POLYNOM\n");
                  #endif
                  $$ = powPolynomStatement((polynomMember*)$1, $3);

                }
                | POLYNOM '*' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM * POLYNOM to POLYNOM\n");
                  #endif
                  
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }
                | POLYNOM '+' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM + POLYNOM to POLYNOM\n");
                  #endif
                  summPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                }
                | POLYNOM '-' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM - POLYNOM to POLYNOM\n");
                  #endif
                  substractPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;

                }


;

EQUATION:       VAR '=' POLYNOM ';'
                {
                  addVariable($1, (polynomMember*)$3);
                  #ifdef DEBUG
                  printPolynom((polynomMember*)$3);
                  printf("=Adding new var\n");
                  #endif
                }
                | EQUATION VAR '=' POLYNOM ';'
                {
                  addVariable((char)$2, (polynomMember*)$4);
                  #ifdef DEBUG
                  printPolynom((polynomMember*)$4);
                  printf("=Adding again new var\n");
                  #endif
                }



FACTOR:         INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM to factor\n");
                  #endif
                  $$ = $1;
                }
                |
                INITIAL_POLYNOM '*' INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM to factor\n");
                  #endif
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }
                |
                FACTOR '*' INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM to factor\n");
                  #endif
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }



INITIAL_POLYNOM:        
                ATOM
                {
                  $$ = createPolynom((int)$1, 0, 0);
                }
                | LETTER
                {
                  char a = $1;
                  $$ = createPolynom(1, 1, a);
                }
                |
                INITIAL_POLYNOM '^' INITIAL_POLYNOM
                {
                  $$ = powPolynomStatement((polynomMember*)$1, $3);

                }
                | INITIAL_POLYNOM INITIAL_POLYNOM
                {
                  $$ = multiplePolynomByPolynom((polynomMember*)$2, (polynomMember*)$1); 
                }
                | '(' POLYNOM ')'
                {
                  #ifdef DEBUG
                  printf("From polynom to INITIAL_POLYNOM\n");
                  #endif
                  $$ = $2;
                }
                | VAR
                {
                  #ifdef DEBUG
                  printf("=====From var to POLYNOM=====\n");
                  #endif
                  polynomMember* tmp = createPolynom(0, 0, 0);
                  summPolynom(tmp, getVariable($1));
                  $$ = tmp;
                }
                /* |  INITIAL_POLYNOM '*' INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM * INITIAL_POLYNOM to INITIAL_POLYNOM\n");
                  #endif
                
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                } */
;




ATOM:           NUM 
                {
                  $$ = $1;
                }
                | ATOM NUM 
                {
                  $$ = $1*10 + $2;
                }
;

%%