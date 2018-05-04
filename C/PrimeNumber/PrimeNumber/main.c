//  Find primes from 2 to 1000
#include <stdio.h>

int 
is_prime(int x)
{
    for (int d = 2; d < x; ++d) if(x %d == 0 || x %d+2 == 0) return 0;
    return 1;
}

int 
main(void)
{
    int p = 1000;
    while (p-- > 2) if(is_prime(p) == 1) printf("%i, ", p);
}

