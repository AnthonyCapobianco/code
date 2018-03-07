#include <stdio.h>
#include <stdlib.h>

#ifndef ___MATRIX_CALC_INCLUDED___
#define ___MATRIX_CALC_INCLUDED___

typedef struct MATRIX
{
    char* name;
    int *array;
} M;

#define mArr(...) M* mArr[] = {__VA_ARGS__, NULL}


M* newMatrix(char*, int*);
void freeMatrix(M* arr[]);

/*
 * in a(i,j) a is an element of the matrix 
 * i is the position on the ligne (x axis) and
 * j is the position on the columns (y axis). 
 */
M* newMatrix(char* matrixName, int* matrix)
{
    M *p = malloc(sizeof(M));
    
    p->name = matrixName;
    p->array = matrix;
    
    return(p);
}

void freeMatrix(M* arr[])
{
    for (int i = 0; arr[i] != NULL; ++i) free(arr[i]);
}

#endif