#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define ARR_END 0
#define DEBUG 1



/* Type drug of type struct */
typedef struct D
{   char* name;
    int* doses;
} drug;

/* Functions Declarations */
drug newDrug(char*, int*, short);
drug* showObj(drug* ptr[]); 
int showDoses(drug*);
void setPath(char*);
void printd(drug* arrPtr[]);
int makeSelection(char*);

int main(void)
{    #define m(...) (int[]) {__VA_ARGS__, 0}, 0
#define n(...) (int[]) {__VA_ARGS__, 0}, 1
    drug ritalin = newDrug("Ritalin", m(5, 10, 15, 20))
       , concerta = newDrug("Concerta", (36, 72))
       , effexor = newDrug("Effexor", f(225))
       , xanax = newDrug("Xanax", f(250, 5000, 1000, 1500, 200))
       , akton = newDrug("Akton", f(1, 2, 3, 4))
       , zolpidem = newDrug("Zolpidem", f(5, 10))
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

    setPath("/Users/Muddy/Desktop/log.txt"); 
    printd(arrPtr);

    return(0);
}

/* Struct constructor for type drug */
drug newDrug(char* dName, int* dDoses, short isNanoGram)
{
    return((drug) {.name = dName, .doses = dDoses});
}


#ifndef DRUGIO_FILE_PATH
#define DRUGIO_FILE_PATH

    const char* drugioFilePath;
    void setPath(char* s)
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

    #define USE_FILE (DEBUG) ? stdout : fp
    
    fprintf(USE_FILE,"[%s] %s %d mg\n", theDate, p->name, p->doses[d]);
    
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
    
    for (int i = 0; ptr->doses[i] != ARR_END ; ++i, ++ident) printf("[%c] %d mg\n", ident, ptr->doses[i]); 

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
