#ifndef POLYNOM_H
#define POLYNOM_H
// #include <ctype.h>
#include <stdint.h>
#define YYSTYPE uint64_t
#include <stdio.h>
#include <malloc.h>
typedef struct polynomMember
{
    char base;
    int factor;
    int degree;
    struct polynomMember* nextMember;   
} polynomMember;



void addToVariables(char var);
void addToPolynoms(polynomMember* poly);
void addVariable(char var, polynomMember* poly);
polynomMember* getVariable(char var);

polynomMember* summVariableAndPolynom(char var, polynomMember* poly);
void addPolynomToVariable(char var, polynomMember* poly);

void duplicatePolynom(polynomMember* dst, polynomMember* src);

polynomMember* createPolynom(int initFactor, int initDegree, char initBase);
void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void multiplePolynomByFactor(polynomMember* firstPolynom, int factor);
polynomMember* powPolynom(polynomMember* polynom, int deg);
// void powPolynomStatement(polynomMember* polynom, int deg);
void printPolynom(polynomMember* polynom);
void checkPolynomBases(polynomMember* firstPolynom, polynomMember* secondPolynom);
void sortPolynom(polynomMember* poly);
void printPolynomDebug(polynomMember* poly);
void changePolynomBase(polynomMember* poly, char newBase);

#endif
