#include <stdio.h>

int main(void) 
{
    // Dicision get's rid of reacurent digit float innacuracy for additions: 
    float boat = (1.F/3) // Note that I used 1.0 and not 1
        , sink = (2.0/3) // 1 is an int while 1.0 or 1.F is a float. 
        , fSum = (boat + sink)
        ;
    printf("%.21f", fSum);
    return(0);
}
