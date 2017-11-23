//  Find primes between 2 and 1000
#include <iostream>
using namespace std;
bool isPrime(int);
int main(int argc, const char * argv[]) {

    int p = 1000;
    //  Logic:
    while (p --> 2) {   if(isPrime(p) == 1) cout << p << ", ";  }
    return 0;
}
bool isPrime(int x){
    //  Variables:
    int d;
    //  Logic:
    for (d = 2; d < x; ++d) {
        if(x %d == 0){ return 0; }
    }
    return 1;
}

