#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef DRUGIO_ARR_END
#define DRUGIO_ARR_END 0.0L
#endif
#ifndef DRUGIO_DEBUG
#define DRUGIO_DEBUG 0
#endif

#ifndef DRUGIO_H_INCLUDED
#define DRUGIO_H_INCLUDED

/* Type drug of type struct */
typedef struct D
{   char* name;
    float* doses;
} drug;

/* Functions Definitions */
drug newDrug(char*, float*);
void printd(drug* arrPtr[]);

drug* showObj(drug* ptr[]); 
int showDoses(drug*); 
int makeSelection(char*);

/* Struct constructor for type drug */
drug newDrug(char* dName, float* dDoses)
{
    return((drug) {.name = dName, .doses = dDoses});
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

    drug* p = showObj(arrPtr); int d = showDoses(p);
    
    #ifndef DRUGIO_USE_FILE
    #define DRUGIO_USE_FILE (DRUGIO_DEBUG) ? stdout : fp
    #endif
    
    fprintf(DRUGIO_USE_FILE,"[%s] %s %2g mg\n", theDate, p->name, p->doses[d]);
    
    fclose(fp);
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
    
    for (int i = 0; ptr->doses[i] != DRUGIO_ARR_END ; ++i, ++ident) printf("[%c] %2g mg\n", ident, ptr->doses[i]); 

    return( (int) (makeSelection(&ident)) );
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
            if (c[0] >= 'a' && c[0] <= *lastObj) break; 
            else 
            { 
                DRUGIO_ERR(DRUGIO_OOR); 
                exit(-1); 
            }
        }
    } while (c + strlen(c) != NULL);
    
    return((int) (c[0] - 'a'));
}
#endif
