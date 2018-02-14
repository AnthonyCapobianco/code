#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char LON[51];
    scanf("%s", LON);
    fprintf(stderr, "%s", LON);
    char LAT[51];
    scanf("%s", LAT);
    fprintf(stderr, "%s", LAT);
    int N;
    scanf("%d", &N); fgetc(stdin);
    for (int i = 0; i < N; i++) {
        char DEFIB[257];
        fgets(DEFIB, 257, stdin);
        fprintf(stderr, "%s", DEFIB);
    }


    printf("answer\n");

    return 0;
}
