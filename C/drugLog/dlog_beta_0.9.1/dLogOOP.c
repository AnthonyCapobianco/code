#include "drugio.h"

int main(void)
{    
    
    drugList( newDrug("Ritalin", mg(5, 10, 15, 20))
            , newDrug("Concerta", mg(36, 72))
            , newDrug("Effexor", mg(225))
            , newDrug("Xanax", ng(250, 500, 1000, 1500, 2000))
            , newDrug("Akton", mg(1, 2, 3, 4))
            , newDrug("Zolpidem", mg(5, 10, 15))
            );

    drugioSetPath("/Users/Muddy/Desktop/log.txt"); 
    printd(drugList);

    return(0);
}
