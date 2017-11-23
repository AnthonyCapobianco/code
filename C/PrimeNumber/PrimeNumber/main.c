//  Find primes from 2 to 1000
#include <stdio.h>
int isPrime(int x){
    int d = 2;
    for (; d < x; ++d) { if(x %d == 0 || x %d+2 == 0) return 0; }
    return 1;//	Omitted else
}
int main(){
    int p = 1000;
    while (p --> 2) { if(isPrime(p) == 1) printf("%i, ", p); }
    return 0;
}

