#include "polynom.h"

char localVariables[26];
polynomMember* localPolynoms[26];

int localVariablesLen = 0, localPolynomsLen = 0;

polynomMember* createPolynom(int initFactor, int initDegree, char initBase)
{
    polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
    tmp->factor = initFactor;
    tmp->degree = initDegree;
    tmp->base = initBase;
    tmp->nextMember = NULL;
    return tmp;
}

void summPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    checkPolynomBases(firstPolynom, secondPolynom);
    if (firstPolynom->base != 0) secondPolynom->base = firstPolynom->base;
    else firstPolynom->base = secondPolynom->base;

    polynomMember* counter;
    counter = firstPolynom;
    while (counter->nextMember != NULL)
    {
        counter = counter->nextMember;
    }


    polynomMember* nextMemberFirst = firstPolynom->nextMember;
    
    for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
    {
        int added = 0;
        for ( polynomMember* counterTmp =  firstPolynom; counterTmp != NULL; counterTmp = counterTmp->nextMember)
        {
            if(counterTmp->degree == secondMember->degree)
            {
                counterTmp->factor += secondMember->factor;
                added = 1;
                break;
            }
        } 
        if (added) continue;

        polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
        tmp->degree = secondMember->degree;
        tmp->factor = secondMember->factor;
        tmp->base = secondMember->base;

        tmp->nextMember = NULL;
        
        counter->nextMember = tmp;
        counter = counter->nextMember;
    }
    // printPolynom(firstPolynom);
}

void substractPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    checkPolynomBases(firstPolynom, secondPolynom);
    if (firstPolynom->base != 0) secondPolynom->base = firstPolynom->base;
    else firstPolynom->base = secondPolynom->base;
    
    polynomMember* counter;
    counter = secondPolynom;
    counter->factor *= -1;

    while (counter->nextMember != NULL)
    {
        printf("fac: %d\n", counter->factor);
        counter = counter->nextMember;
        counter->factor *= -1;
    }

    summPolynom(firstPolynom, secondPolynom);


    // polynomMember* nextMemberFirst = firstPolynom->nextMember;
    
    // for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
    // {
    //     int added = 0;
    //     for ( polynomMember* counterTmp =  firstPolynom; counterTmp != NULL; counterTmp = counterTmp->nextMember)
    //     {
    //         if(counterTmp->degree == secondMember->degree)
    //         {
    //             counterTmp->factor -= secondMember->factor;
    //             added = 1;
    //             break;
    //         }
    //     } 
    //     if (added) continue;

    //     polynomMember* tmp = (polynomMember*)malloc(sizeof(polynomMember));
    //     tmp->degree = secondMember->degree;
    //     tmp->factor = -secondMember->factor;
    //     tmp->nextMember = NULL;
        
        
    //     counter->nextMember = tmp;
    //     counter = counter->nextMember;
    // }
    // printPolynom(firstPolynom);
}

polynomMember* multiplePolynomByPolynom(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    checkPolynomBases(firstPolynom, secondPolynom);
    if (firstPolynom->base != 0) secondPolynom->base = firstPolynom->base;
    else firstPolynom->base = secondPolynom->base;

    polynomMember* tmp = NULL;
    if (firstPolynom->base != 0)
    {
        tmp = createPolynom(0, 1, firstPolynom->base);
    }
    else
    {
        tmp = createPolynom(0, 1, secondPolynom->base);
    }
    

    for(polynomMember* firstMember = firstPolynom; firstMember != NULL; firstMember = firstMember->nextMember)
    {
        for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
        {
            summPolynom(tmp, createPolynom(firstMember->factor * secondMember->factor, firstMember->degree + secondMember->degree, firstMember->base));
        }
    }
    return tmp;
}

void multiplePolynomByFactor(polynomMember* firstPolynom, int factor)
{
    firstPolynom->factor *= factor; 
    // printPolynom(firstPolynom);
}

void powPolynom(polynomMember* polynom, int deg)
{
    polynom->degree *= deg;
    // printf("Pow poly: ");
    // printPolynom(polynom);
}

void printPolynom(polynomMember* polynom)
{
    sortPolynom(polynom);
    for(polynomMember* member = polynom; member != NULL; member = member->nextMember)
    {
        // printPolynomDebug(member);
        if(member->factor == 0) continue;
        if (member->degree == 0)
        {
            if(member->factor >= 0) printf("+%d", member->factor);
            else printf("%d", member->factor);
        }
        else if (member->degree == 1)
        {
            if(member->factor >= 0) printf("+%d%c", member->factor, member->base);
            else printf("%d%c", member->factor, member->base);
        }
        else 
        {
            if(member->factor >= 0) printf("+%d%c^%d", member->factor, member->base, member->degree);
            else printf("%d%c^%d", member->factor, member->base, member->degree);
        }
    }
    // printf("\n");
}

void checkPolynomBases(polynomMember* firstPolynom, polynomMember* secondPolynom)
{
    if ((firstPolynom->base != secondPolynom->base) && firstPolynom->base != 0 && secondPolynom->base != 0)
    {
        printf("Can't operate with different bases polynoms: %c <=> %c\n", firstPolynom->base, secondPolynom->base);
        exit(1);
    }
}

void sortPolynom(polynomMember* poly)
{
    int swapped;
    polynomMember *ptr1;
    polynomMember *lptr = NULL;
 
    // Проверка на пустой список
    if (poly == NULL)
        return;
 
    do {
        swapped = 0;
        ptr1 = poly;
 
        while (ptr1->nextMember != lptr) {
            if (ptr1->degree < ptr1->nextMember->degree) {
                // Обмен значениями между ptr1 и ptr1->nextMember
                char tempBase = ptr1->base;
                int tempFactor = ptr1->factor;
                int tempDegree = ptr1->degree;
                ptr1->base = ptr1->nextMember->base;
                ptr1->factor = ptr1->nextMember->factor;
                ptr1->degree = ptr1->nextMember->degree;
                ptr1->nextMember->base = tempBase;
                ptr1->nextMember->factor = tempFactor;
                ptr1->nextMember->degree = tempDegree;
                swapped = 1;
            }
            ptr1 = ptr1->nextMember;
        }
        lptr = ptr1;
    } while (swapped);
}

void printPolynomDebug(polynomMember* poly)
{
    printf("\n{\n\tbase: %c\n\tfactor: %d\n\tdegree: %d\n\tNext member: %p\n}\n",
    poly->base, poly->factor, poly->degree, poly->nextMember);
}

void changePolynomBase(polynomMember* poly, char newBase)
{
    polynomMember* counter;
    counter = poly;
    while (counter != NULL)
    {
        counter->base = newBase;
        counter = counter->nextMember;
    }
}

void addVariable(char var, polynomMember* poly)
{
    addToVariables(var);
    addToPolynoms(poly);
}

void addToVariables(char var)
{
    localVariables[localVariablesLen] = var; 
    localVariablesLen++;
}

void addToPolynoms(polynomMember* poly)
{
    if (localVariablesLen - 1 != localPolynomsLen)
    {
        printf("Something went wrong with vars. . .\n");
        exit(-1);
    }
    if (localPolynoms[localPolynomsLen] != NULL)
    {
        free(localPolynoms[localPolynomsLen]);
    }
    localPolynoms[localPolynomsLen] = poly;
    localPolynomsLen++;
}

polynomMember* getVariable(char var)
{
    int i;
    for(i = 0; i < 26; i++)
    {
        if(localVariables[i] == var)
            return localPolynoms[i];
    }
    return NULL;
}
polynomMember* summVariableAndPolynom(char var, polynomMember* poly)
{
    polynomMember* secondPoly = getVariable(var);
    if(secondPoly == NULL) return NULL;
    summPolynom(poly, secondPoly);
    return poly;
}

void addPolynomToVariable(char var, polynomMember* poly)
{
    int i;
    for (i = 0; i < 26; i++)
    {
        if(localVariables[i] == var)
        {
            summPolynom(localPolynoms[i], poly);
        }
    }
}

// void duplicatePolynom(polynomMember* dst, polynomMember* src)
// {

// }