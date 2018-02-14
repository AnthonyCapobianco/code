#include <stdio.h>

#define DEBUG 1
#include "drugio.h"

#define f(...) (float[]) {__VA_ARGS__, 0.0} 

int main(void)
{
    drug ritalin = newDrug("Ritalin", f(5.0, 10.0, 15.0, 20.0))
       , concerta = newDrug("Concerta", f(36.0, 72.0))
       , effexor = newDrug("Effexor", f(225.0))
       , xanax = newDrug("Xanax", f(0.25, 0.5, 1.0, 1.5, 2.0))
       , akton = newDrug("Akton", f(1.0, 2.0, 3.0, 4.0))
       , zolpidem = newDrug("Zolpidem", f(5.0, 10.0))
       ;
     
    /* TODO: Automate this part */
    /* arrPtr[] is an array of pointer to drugs */
    drug* arrPtr[] =
    {  &ritalin
    ,  &concerta
    ,  &effexor
    ,  &xanax
    ,  &akton
    ,  &zolpidem
    ,  NULL
    };
        
    printd("~/Desktop/log.txt", arrPtr);
            
    return(0);
}
