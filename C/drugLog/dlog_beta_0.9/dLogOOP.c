#define DRUGIO_DEBUG 1
#include "drugio.h"

#define mg(...) (int[]) {__VA_ARGS__, 0}, 0
#define ng(...) (int[]) {__VA_ARGS__, 0}, 1

int main(void)
{    
    drug ritalin = newDrug("Ritalin", mg(5, 10, 15, 20))
       , concerta = newDrug("Concerta", mg(36, 72))
       , effexor = newDrug("Effexor", mg(225))
       , xanax = newDrug("Xanax", ng(250, 500, 1000, 1500, 2000))
       , akton = newDrug("Akton", mg(1, 2, 3, 4))
       , zolpidem = newDrug("Zolpidem", mg(5, 10))
       ;
    
    /* TODO: Automate this part */
    /* arrPtr[] is an array of pointer to drugs */
    drug* arrPtr[] =
    {    &ritalin
    ,    &concerta
    ,    &effexor
    ,    &xanax
    ,    &akton
    ,    &zolpidem
    ,    NULL
    };

    drugioSetPath("/Users/Muddy/Desktop/log.txt"); 
    printd(arrPtr);

    return(0);
}
