#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define DEBUG 0

size_t strftime(char *, size_t, const char *, const struct tm *);

typedef struct drugUsed
{
    int dose[6];
    char doseUsed[4]
       , drugUsed[3]
       ;
    char * drugName[3];
    
} drug;

int main(int argc, char **argv)
{
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    
    time(&rawtime);
    info = localtime(&rawtime);
    
    strftime(buffer, 80, "%x - %H:%M", info);
    
    drug med = 
    {
     .dose = {5, 10, 15, 20, 72, 225}
    ,.doseUsed = {'A','B','C','D'}
    ,.drugUsed = {'A','B','C'}
    ,.drugName = {"Concerta", "Effexor", "Rilatin"}
    };
    
    int v = 0
      , x = 0
      ;
    int i;
    char drugChoice = (argc > 1) ? *argv[1] : 0
       , doseChoice = 0
       ;
    
    while (!(drugChoice)) 
    {
        printf("Please select the drug used from the list:\n");
        for (i = 0; i < 3; ++i)
        {
            printf("[%c] %s\n", med.drugUsed[i], med.drugName[i]);
        }
        scanf("%c", &drugChoice);
    }
    //put input to uppercase
    drugChoice = toupper(drugChoice);
    
    //find the position of the input in the array
    while(drugChoice != med.drugUsed[v] && v <= 2) 
      (drugChoice == med.drugUsed[v]) ? v : v++;

    //if the user used a char not found in the table start again
    #define OOR(x) fprintf(stderr,"%c isn't part of the list\n", x)
    if ((drugChoice != med.drugUsed[v] && v >= 2) && drugChoice) OOR(drugChoice);

    //print the possible doses
    x = (!v) ? 4 : (v == 1) ? 5 : x;
    
    //ask for dose
    doseChoice = (!doseChoice && x < 3 && argc > 2) ? *argv[2] : 0;
    while (!doseChoice && x < 3) 
    {
        printf("Please select the dose used from the list:\n");
        for (i = 0; i < 4; ++i) printf("[%c]%i mg\n", med.doseUsed[i], med.dose[i]);
        scanf(" %c", &doseChoice);
    }
    //put input to uppercase
    doseChoice = toupper(doseChoice);
    
    if (!x) while (doseChoice != med.doseUsed[x] && x < 3) (doseChoice == med.doseUsed[x]) ? x : x++;

    //if the user used a char not found in the table start again
    if((doseChoice != med.doseUsed[x] && v >= 4) && doseChoice) OOR(doseChoice);
    
    FILE *fp;
    
    fp = fopen("/Users/Muddy/Desktop/log.txt", "a+");
    #define FILE (DEBUG) ? stdout : fp
    fprintf(FILE,"[%s] %s %i mg\n", buffer, med.drugName[v], med.dose[x]);
    fclose(fp);
    
    return(0);
}