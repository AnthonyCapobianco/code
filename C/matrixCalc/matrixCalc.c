/* 20/02/2018 */
#include "mcalc.h"
/*
 * Le produit d’une matrice de genre m x n par un réel k est une
 * matrice de genre m x n dont tout élément est multiplié par le réel k
 */
/* Fuction scalarMultiply */

/*
 * La somme de deux matrices de genre m x n est 
 * une matrice de genre m x n dont tout élément est la 
 * somme des éléments correspondants des matrices additionnées
 */
/* Function addition */
int main(void) 
{
    int a[3][3] = 
    { {1,2,3}
    , {4,5,6}
    , {7,8,9}
    };
    
    int b[3][4] =
    { {1,2,3,4}
    , {2,3,4,5}
    , {3,4,5,6}
    };

    mArr( newMatrix("A", *a)
        , newMatrix("B", *b)
        );
    return(0);
}
