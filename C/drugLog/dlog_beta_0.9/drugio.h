#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef DRUGIO_ARR_END
#define DRUGIO_ARR_END 0
#endif
#ifndef DRUGIO_DEBUG
#define DRUGIO_DEBUG 0
#endif

#ifndef DRUGIO_H_INCLUDED
#define DRUGIO_H_INCLUDED

/* Type drug of type struct */
typedef struct DRUG
{   char* name;
    int* doses;
    short isNanoGram;
} drug;

/* Type diPtr of type struct */
typedef struct PRT_DRUG_INT
{    int iPtr;
     drug* dPtr;
} diPtr;

/* Functions Definitions */
drug newDrug(char*, int*, short);
void printd(drug* arrPtr[]);

diPtr drugioMenu(drug* ptr[]);
int makeSelection(char*);

/* Struct constructor for type drug */
drug newDrug(char* dName, int* dDoses, short isNG)
{
    return((drug) {.name = dName, .doses = dDoses, .isNanoGram = isNG});
}

/* File Path */
#ifndef DRUGIO_FILE_PATH
#define DRUGIO_FILE_PATH

    const char* drugioFilePath;
    void drugioSetPath(char* s)
    {
        drugioFilePath = s;
    }

#endif

/* Print the end result */
void printd(drug* arrPtr[])
{
    FILE *fp; fp = fopen(drugioFilePath, "a+");
    
    char* formatedDate(void); char* theDate = (char *) (formatedDate());

    diPtr dip = drugioMenu(arrPtr);
    drug* p = dip.dPtr; int d = dip.iPtr;
    
    #ifndef DRUGIO_USE_FILE
    #define DRUGIO_USE_FILE (DRUGIO_DEBUG) ? stdout : fp
    #endif
    
    if (p->isNanoGram) fprintf(DRUGIO_USE_FILE,"[%s] %s %2g mg\n", theDate, p->name, (    (float) p->doses[d] / 1000));
    else fprintf(DRUGIO_USE_FILE,"[%s] %s %d mg\n", theDate, p->name, p->doses[d]);
    
    fclose(fp);
}

/* Print drug names */
diPtr drugioMenu(drug* ptr[])
{
    char ident; 
    int i;
    int d;
    drug* idedDrug;

DRUGIO_MENU:
    while(1)
    {
        puts("Please type the letter conresponding to the drug taken");
        puts("then press the enter key.\n");
    
        for (ident = 'a', i = 0; ptr[i] != NULL; ++i, ++ident) printf("[%c] %s\n", ident, ptr[i]->name);
    
        d = (int) (makeSelection(&ident));
        if (d == -1) goto DRUGIO_MENU;
        else idedDrug = ptr[d];
        
        printf("\nDoses for %s:\n\n", idedDrug->name);
        for (ident = 'a', i = 0; idedDrug->doses[i] != DRUGIO_ARR_END ; ++i, ++ident) 
        {
            if (idedDrug->isNanoGram) printf("[%c] %2g mg\n", ident, (float) (idedDrug->doses[i] / 1000.0)); 
            else printf("[%c] %d mg\n", ident, idedDrug->doses[i]);
        }   
        
        d = (int) (makeSelection(&ident));
        if (d == -1) goto DRUGIO_MENU;
        else return((diPtr) { .iPtr = d, .dPtr = idedDrug});
    }
}

/* Make Selection (read user input) */
int makeSelection(char* lastObj)
{
    char c[20];

    do
    {
        printf("> "); 
        
        #ifndef DRUGIO_ERR
        #define DRUGIO_ERR(x) fprintf(stderr, x)
        #endif
        #ifndef DRUGIO_EOF
        #define DRUGIO_EOF "Error: Your choice isn't correct\n"
        #endif
        #ifndef DRUGIO_OOR
        #define DRUGIO_OOR "Error: The character you entered is not part of the selection\n"
        #endif
        
        if (!fgets(c, 20, stdin)) 
        { 
            DRUGIO_ERR(DRUGIO_EOF); 
            exit(-1); 
        } 
        else 
        {
            if (!strncmp(c, "exit", 4) || !strncmp(c, "quit", 4)) exit(0);
            if (!strncmp(c, "back", 4)) return(-1);
            if (c[0] >= 'a' && c[0] <= (*lastObj - 1)) return((int) (c[0] - 'a')); 
            else 
            { 
                DRUGIO_ERR(DRUGIO_OOR); 
                return(-1); 
            }
        }
    } while (c + strlen(c) != NULL);
}

/* Date parsing and formating */
char* formatedDate()
{
    size_t strftime(char *, size_t, const char *, const struct tm *);
    
    time_t rawtime; struct tm *info;
    static char buffer[17]; /* 16 + '\0' */
    time(&rawtime); info = localtime(&rawtime);
    
    strftime(buffer, 17, "%x - %H:%M", info);
    
    return(buffer);
}

#endif
