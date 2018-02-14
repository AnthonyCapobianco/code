#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifndef ARR_END
#define ARR_END 0.0L
#endif
#ifndef DEBUG
#define DEBUG 0
#endif
#ifndef DRUGIO_H_INCLUDED
#define DRUGIO_H_INCLUDED

#define uint unsigned int 

/* Type drug of type struct */
typedef struct D
{   char* name;
    float* doses;
} drug;

/* Functions Definitions */
drug newDrug(char*, float*); 
drug* showObj(drug* ptr[]); 
int showDoses(drug*);
void printd(char* FILE_PATH, drug* arrPtr[]);

/* Make Selection (read user input) */
int makeSelection(char* lastObj)
{
    char c[20];

    do
    {
        printf("> "); 
        
        #define ERR(x) fprintf(stderr, x); exit(-1)
        #define _EOF "Error: Your choice isn't correct\n"
        #define OOR "Error: The character you entered is not part of the selection\n"
        
        if (!fgets(c, 20, stdin)) { ERR(_EOF); }
        if (c[0] >= 'a' && c[0] <= *lastObj) break; 
        else { ERR(OOR); }
        
        c[strlen(c) - 1] = 0;
        if (!strcmp(c, "exit")) exit(0);
        
    } while (c + strlen(c) != NULL);
    
    return((int) (c[0] - 'a'));
}

/* Print the end result */
void printd(char* FILE_PATH, drug* arrPtr[])
{
    drug* p = showObj(arrPtr); 
    int d = showDoses(p);

    FILE *fp; fp = fopen(FILE_PATH, "a+");
    char* formatedDate(void); char* theDate = (char *) (formatedDate());
    
    #define FILE (DEBUG) ? stdout : fp
    
    fprintf(FILE,"[%s] %s %2.2g mg\n", theDate, p->name, p->doses[d]);
    
    fclose(fp);
}

/* Struct constructor for type drug */
drug newDrug(char* dName, float* dDoses)
{
    return((drug) {.name = dName, .doses = dDoses});
}

/* Print drug names */
drug* showObj(drug* ptr[])
{
    char ident = 'a';

    puts("Please type the letter conresponding to the drug taken");
    puts("then press the enter key.\n");
    
    for (int i = 0; ptr[i] != NULL; ++i, ++ident) printf("[%c] %s\n", ident, ptr[i]->name);
    
    return( ptr[(int) (makeSelection(&ident))] );
}

/* Print drug doses */
int showDoses(drug* ptr)
{
    char ident = 'a';
    
    printf("\nDoses for %s:\n\n", ptr->name);
    
    for (int i = 0; ptr->doses[i] != ARR_END ; ++i, ++ident) printf("[%c] %2g\n", ident, ptr->doses[i]); 

    return( (int) (makeSelection(&ident)) );
}

/* Date parsing and formating */
char* formatedDate()
{
    size_t strftime(char *, size_t, const char *, const struct tm *);
    
    time_t rawtime;
    struct tm *info;
    static char buffer[16];
    
    time(&rawtime); info = localtime(&rawtime);
    
    strftime(buffer, 16, "%x - %H:%M", info);
    
    return(buffer);
}
#endif
