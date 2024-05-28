#include "polynom.h"

char localVariables[26];
polynomMember* localPolynoms[26];

long localVariablesLen = 0, localPolynomsLen = 0;

polynomMember* createPolynom(long initFactor, long initDegree, char initBase)
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
        long added = 0;
        for ( polynomMember* counterTmp =  firstPolynom; counterTmp != NULL; counterTmp = counterTmp->nextMember)
        {
            if(counterTmp->degree == secondMember->degree)
            {
                counterTmp->factor += secondMember->factor;
                // secondMember->factor = 0;
                // secondMember->degree = 0;
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
        // printf("fac: %d\n", counter->factor);
        counter = counter->nextMember;
        counter->factor *= -1;
    }

    summPolynom(firstPolynom, secondPolynom);


    // polynomMember* nextMemberFirst = firstPolynom->nextMember;
    
    // for(polynomMember* secondMember = secondPolynom; secondMember != NULL; secondMember = secondMember->nextMember)
    // {
    //     long added = 0;
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
    // malloc()
    
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
    // printf("\nMultiplying :\n");
    // printPolynom(firstPolynom);
    // printf("\nby\n");
    // printPolynom(secondPolynom);
    // printf("\nresult:\n");
    // printPolynom(tmp);
    // printf("\n------------------------\n");
    return tmp;
}

void multiplePolynomByFactor(polynomMember* firstPolynom, long factor)
{
    // firstPolynom->factor *= factor; 
    // printPolynom(firstPolynom);
    polynomMember* counter;
    counter = firstPolynom;
    counter->factor *= factor;
    while (counter->nextMember != NULL)
    {
        // printf("fac: %d\n", counter->factor);
        counter = counter->nextMember;
        counter->factor *= factor;
    }
}

polynomMember* powPolynom(polynomMember* polynom, long deg)
{
    sortPolynom(polynom);
    if (polynom->factor == 0 && deg == 0) 
    {
        printf("Error: 0^0\n");
        exit(1);
    }
    polynomMember* tmp = createPolynom(1, 0, polynom->base);
    for (long i = 0; i < deg; i++)
    {
        tmp = multiplePolynomByPolynom(tmp, polynom);
    }
    return tmp;
}

polynomMember* powPolynomStatement(polynomMember* polynom, polynomMember* deg)
{
    sortPolynom(deg);
    sortPolynom(polynom);
    if (polynom->factor == 0 && deg->factor == 0) 
    {
        printf("Error: 0^0\n");
        exit(1);
    }
    
    while(deg->factor == 0 && deg->nextMember != NULL) deg = deg->nextMember;
    if (deg->degree == 0)
    {
        polynomMember* tmp = createPolynom(1, 0, polynom->base);
        
        for (long i = 0; i < deg->factor; i++)
        {
            // printPolynom(tmp);
            tmp = multiplePolynomByPolynom(tmp, polynom);
        }
        return tmp;
    }
    printf("Error: trying to polynom ^ polynom\n");
    // printPolynomDebug(deg);
    exit(1);
}

void printPolynom(polynomMember* polynom)
{
    sortPolynom(polynom);
    polynomMember* member = polynom;
    // printPolynomDebug(polynom);

    while(member->factor == 0 && member->nextMember != NULL)
    {
        member = member->nextMember;
    }

    
    if (member->degree == 0)
    {
        printf("%d", member->factor);
    }
    else
    {
        if (member->factor != 1 && member->factor != -1)  printf("%d", member->factor);
        if (member->factor == -1)  printf("-");
        printf("%c",member->base);
        if (member->degree > 1) printf("^%d", member->degree);
        
    }
    member = member->nextMember;
    for(member; member != NULL; member = member->nextMember)
    {
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
    long swapped;
    polynomMember *ptr1;
    polynomMember *lptr = NULL, *dptr = poly;
 
    if (poly == NULL)
        return;
 
    do {
        swapped = 0;
        ptr1 = poly;
 
        while (ptr1->nextMember != lptr) {
            if (ptr1->degree < ptr1->nextMember->degree) {
                // Обмен значениями между ptr1 и ptr1->nextMember
                char tempBase = ptr1->base;
                long tempFactor = ptr1->factor;
                long tempDegree = ptr1->degree;
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
    addToPolynoms(poly, addToVariables(var));
}

long addToVariables(char var)
{
    for (long i = 0; i < localVariablesLen; i++)
    {
        if (localVariables[i] == var)
        {
            return i;
        }
    }
    localVariables[localVariablesLen] = var; 
    // localVariablesLen++;
    return localVariablesLen++;
}

void addToPolynoms(polynomMember* poly, long position)
{
    if (localPolynoms[position] != NULL)
    {
        free(localPolynoms[position]);
        localPolynoms[position] = NULL;
        localPolynomsLen--;
    }
    localPolynoms[position] = poly;
    localPolynomsLen++;
}

polynomMember* getVariable(char var)
{
    long i;
    for(i = 0; i < 26; i++)
    {
        if(localVariables[i] == var)
            return localPolynoms[i];
    }

    printf("Variable '%c' not found\n", var);
    exit(1);
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
    long i;
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