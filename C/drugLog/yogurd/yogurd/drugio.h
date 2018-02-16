/*
 *  This program is designed to provide an easy way for
 *  users to log doses of the medication(s) they use.
 *  Copyright (C) 2018 Anthony Capobianco
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

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

#ifndef mg
#define mg(...) (int[]) {__VA_ARGS__, 0}, 0

#else
#ifndef drugio_mg
#define drugio_mg(...) (int[]) {__VA_ARGS__, 0}, 0
#endif

#endif

#ifndef ng
#define ng(...) (int[]) {__VA_ARGS__, 0}, 1

#else
#ifndef drugio_ng
#define drugio_ng(...) (int[]) {__VA_ARGS__, 0}, 1
#endif

#endif

#ifndef drugList
#define drugList(...) drug* drugList[] = {__VA_ARGS__, NULL}

#else
#ifndef drugio_drugList
#define drugio_drugList(...) drug* drugList[] = {__VA_ARGS__, NULL}
#endif

#endif

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

/* Function prototype */
static drug* newDrug(char*, int*, short);
/* Struct constructor for type drug pointer */
static drug* newDrug(char* dName, int* dDoses, short isNG)
{
    drug* p = malloc(sizeof(drug));
    p->name = dName; p->doses = dDoses; p->isNanoGram = isNG;
    return(p);
}

/* Function prototype */
static void drugioDestructor(drug* arrPtr[]);
/* Struct destructor for drugs */
static void drugioDestructor(drug* arrPtr[])
{
    for (int i = 0; arrPtr[i] != NULL; i++) free(*(arrPtr + i));
}

/* Function prototype */
int makeSelection(char*);
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
            exit(EXIT_FAILURE);
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

/* Function prototype */
static diPtr drugioMenu(drug* ptr[]);
/* Print drug names */
static diPtr drugioMenu(drug* ptr[])
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

/* Function prototype */
char* formatedDate(void);
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

/* Function prototype */
short runAgain(void);
/* Ask to run again */
short runAgain()
{
    char c[4];

    printf("Do you want to run this again? (Y/N): ");
    if(!fgets(c, 4, stdin))
    {
        DRUGIO_ERR(DRUGIO_EOF);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (c[0] == 'y' || c[0] == 'Y') return(1);
        else return(0);
    }
}

/* File Path */
#ifndef DRUGIO_FILE_PATH
#define DRUGIO_FILE_PATH

    /* Global constant */
    const char* drugioFilePath;    
    /* Function prototype */
    void drugioSetPath(char*);
    /* Set path of file to log to */
    void drugioSetPath(char* s)
    {
        drugioFilePath = s;
    }

#endif

/* Function prototype */
void printd(drug* arrPtr[]);
/* Print the end result */
void printd(drug* arrPtr[])
{
    FILE *fp; fp = fopen(drugioFilePath, "a+");

    char* formatedDate(void);
    do
    {
        char* theDate = (char *) (formatedDate());
        diPtr dip = drugioMenu(arrPtr);
        drug* p = dip.dPtr; int d = dip.iPtr;

        #ifndef DRUGIO_USE_FILE
        #define DRUGIO_USE_FILE (DRUGIO_DEBUG) ? stdout : fp
        #endif

        if (p->isNanoGram) fprintf(DRUGIO_USE_FILE,"[%s] %s %2g mg\n", theDate, p->name, ((float) p->doses[d] / 1000));
        else fprintf(DRUGIO_USE_FILE,"[%s] %s %d mg\n", theDate, p->name, p->doses[d]);
    } while (runAgain());
    fclose(fp); drugioDestructor(arrPtr);
}

#endif
