#ifndef POLYNOM_H
#define POLYNOM_H
// #include <ctype.h>
#include <stdint.h>
#define YYSTYPE uint64_t
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef struct polynomMember
{
    char base;
    long factor;
    long degree;
    struct polynomMember* nextMember;   
} polynomMember;



long addToVariables(char var);
void addToPolynoms(polynomMember* poly, long position);
void addVariable(char var, polynomMember* poly);
polynomMember* getVariable(char var);

polynomMember* summVariableAndPolynom(char var, polynomMember* poly);
void addPolynomToVariable(char var, polynomMember* poly);

void duplicatePolynom(polynomMember* dst, polynomMember* src);

polynomMember* createPolynom(long initFactor, long initDegree, char initBase);
void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom);
void multiplePolynomByFactor(polynomMember* firstPolynom, long factor);
polynomMember* powPolynom(polynomMember* polynom, long deg);
polynomMember* powPolynomStatement(polynomMember* polynom, polynomMember* deg);
void printPolynom(polynomMember* polynom);
void checkPolynomBases(polynomMember* firstPolynom, polynomMember* secondPolynom);
void sortPolynom(polynomMember* poly);
void printPolynomDebug(polynomMember* poly);
void changePolynomBase(polynomMember* poly, char newBase);

#endif
