#include <stdio.h>

#define endl printf("\n")


#define swap(x, y) x ^= y; y ^= x; x ^= y
/*
 * The reason as to why this work is actually quite simple. 
 * We start by x = x XOR y. So if x = 1 and y = 0: 
 * x = 1 XOR 0 = 1 
 * y = 1 XOR 0 = 1 <- Note that y was previously 0.
 * x = 1 XOR 1 = 0 <- Note that x was previously 1.
 * We're done. 
 *
 */

int 
main(void) 
{
    int x = 10
      , y = 90
      ;
    
    printf("x:%i\ty:%i", x, y); endl;
    swap(x, y);
    printf("x:%i\ty:%i", x, y); endl;
    
    char s = 's'
       , t = 't'
       ;
      
    printf("s:%c\tt:%c", s, t); endl;
    swap(s, t);
    printf("s:%c\tt:%c", s, t); endl;
    
    return 0;
}