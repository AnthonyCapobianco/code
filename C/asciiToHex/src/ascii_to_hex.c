//
// ascii_to_hex.c
// Created by Anthony Capobianco on 07/03/2018.

#include "ascii_to_hex.h"

extern unsigned char 
printHelp()
{
        puts("Help menu");
        
        puts("-b [int]");
        puts("\tPrints binary form of the int. (Don't put brackets)");
        
        return 0;
        
}

extern void 
printBinaryFromInt(int n)
{
        for (short i = 31; i >= 0; i--) 
                if ((n >> i) > 0) printf("%c%d", (!((i + 1) % 4)) ? ' ' : 0, ((n >> i) & 1));
}