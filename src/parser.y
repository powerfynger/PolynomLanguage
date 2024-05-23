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
                printPolynom($2);
                printf("\n");
              }
              | EQUATION



POLYNOM:        FACTOR
                {
                  $$ = $1;
                  // printPolynom($$);
                  #ifdef DEBUG
                  printf("From factor to poly\n");
                  #endif
                }
                | VAR
                {
                  // printPolynom(getVariable($1));
                  #ifdef DEBUG
                  printf("=====From var to POLYNOM=====\n");
                  #endif
                  polynomMember* tmp = createPolynom(0, 0, 0);
                  summPolynom(tmp, getVariable($1));
                  $$ = tmp;
                }
                /* | '-' VAR
                {
                  // printPolynom(getVariable($2));
                  // printf("=====From var to POLYNOM=====\n");
                  polynomMember* tmp = createPolynom(0, 0, 0);
                  summPolynom(tmp, getVariable($2));
                  multiplePolynomByFactor(tmp, -1);
                  $$ = tmp;
                } */
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
                  // printPolynom((polynomMember*)$1);
                  // printf("\n\n");
                  // printPolynom((polynomMember*)$3);
                                    // printf("\n\n");

                  summPolynom((polynomMember*)$1, (polynomMember*)$3);
                  // // printPolynom((polynomMember*)$1);
                  $$ = $1;
                }
                | POLYNOM '-' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM - POLYNOM to POLYNOM\n");
                  #endif
                  // // printPolynom((polynomMember*)$1);
                  // // printf("\n\n");
                  // // printPolynom((polynomMember*)$3);
                  substractPolynom((polynomMember*)$1, (polynomMember*)$3);
                  $$ = $1;
                  // // printf("\n\n");
                  // // printPolynom((polynomMember*)$1);

                }
                | POLYNOM '^' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From POLYNOM ^ POLYNOM to POLYNOM\n");
                  #endif
                  // powPolynom((polynomMember*)$1, $3);
                  $$ = powPolynomStatement((polynomMember*)$1, $3);
                  // // printf("DEEEECH: ");
                  // // printPolynom($$);

                }
                |  '-' POLYNOM
                {
                  #ifdef DEBUG
                  printf("From -POLYNOM to POLYNOM\n");
                  #endif
                  // // printPolynom((polynomMember*)$1);
                  // // printf("\n\n");
                  // // printPolynom((polynomMember*)$3);
                  multiplePolynomByFactor($2, -1);
                  $$ = $2;
                  // // printf("\n\n");
                  // // printPolynom((polynomMember*)$1);

                }


;

EQUATION:       VAR '=' POLYNOM ';'
                {
                  addVariable($1, $3);
                  #ifdef DEBUG
                  printPolynom($3);
                  printf("=Adding new var\n");
                  #endif
                }
                | EQUATION VAR '=' POLYNOM ';'
                {
                  addVariable($2, $4);
                  #ifdef DEBUG
                  printPolynom($4);
                  printf("=Adding again new var\n");
                  #endif
                }
                /* | VAR '='
                {
                  // printf("Caught them\n");
                } */

FACTOR:         INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM to factor\n");
                  #endif
                  $$ = $1;
                }
                |  INITIAL_POLYNOM '^' INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM ^ INITIAL_POLYNOM to INITIAL_POLYNOM\n");
                  #endif
                  // powPolynom((polynomMember*)$1, $3);
                  $$ = powPolynomStatement((polynomMember*)$1, $3);
                  // // printf("DEEEECH: ");
                  // // printPolynom($$);
                } 


POWER:          ATOM
                {
                  #ifdef DEBUG
                  printf("From atom: %d to power\n", $1);
                  #endif
                  $$ = $1;
                }
                | ATOM '^' POWER 
                {
                  if ($1 == 0 && $3 == 0)
                  {
                    printf("Error 0^0\n");
                    exit(1);
                  }
                  $$ = (int)pow($1, $3);
                  #ifdef DEBUG
                  printf("From atom:%d ^ power:%d to power: %d\n", $1,  $3, $$);
                  #endif
                }
                /* | '-' ATOM 
                {
                  #ifdef DEBUG
                  printf("-ATOM\n");
                  #endif
                  // printf("From atom:%d ^ power:%d to power: %d\n", $1,  $3, $$);
                  $$ = -$2;
                } */

;

INITIAL_POLYNOM:        

                INITIAL_POLYNOM '^' POWER 
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM ^ power:%d to INITIAL_POLYNOM\n", $3);
                  #endif
                  // powPolynom((polynomMember*)$1, $3);
                  $$ = powPolynom((polynomMember*)$1, $3);
                  // // printf("DEEEECH: ");
                  // // printPolynom($$);
                }
                | POWER
                {
                  #ifdef DEBUG
                  printf("From power %d to INITIAL_POLYNOM\n", $1);
                  #endif
                  $$ = createPolynom((polynomMember*)$1, 0, 0);
                  
                }
                | LETTER
                {
                  char a = $1;
                  $$ = createPolynom(1, 1, a);
                  // // printf("Init base: %c\n", a);
                }
                
                | POWER INITIAL_POLYNOM
                {
                  multiplePolynomByFactor((polynomMember*)$2, (int)$1);
                  $$ = $2;
                }
                | '(' POLYNOM ')'
                {
                  #ifdef DEBUG
                  printf("From polynom to INITIAL_POLYNOM\n");
                  #endif
                  $$ = $2;
                  // // // printPolynom($$);
                }
                |  INITIAL_POLYNOM '*' INITIAL_POLYNOM
                {
                  #ifdef DEBUG
                  printf("From INITIAL_POLYNOM * INITIAL_POLYNOM to INITIAL_POLYNOM\n");
                  #endif
                  // // // printPolynom((polynomMember*)$1);
                  // // // printPolynom((polynomMember*)$3);
                  $$ = multiplePolynomByPolynom((polynomMember*)$1, (polynomMember*)$3);
                }
                /* | '-' LETTER
                {
                  // printf("From -LETTER\n");
                  char a = $2;
                  $$ = createPolynom(-1, 1, a);
                } */
;




ATOM:           NUM 
                {
                  // #ifdef DEBUG
                  // printf("Init num: %d\n", $$);
                  $$ = $1;
                }
                | ATOM NUM 
                {
                  // printf("Init new num: %d\n", $$);
                  $$ = $1*10 + $2;
                }
;

%%