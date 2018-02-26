/*
 *  This program is designed to provide an easy way for
 *  users to graphically represent a point on a graph
 *
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
#include "printg.h"

extern void 
printg(unsigned int x, unsigned int y)
{
    printf(G_UP G_LEFT_P);
    
    for (int i = 15; i >= 0; i--)
    {
        if (i  > (int) y)
        {
            printf(G_LEFT);
            printf(G_LEFT_P);
        }
        else if (i == (int) y)
        {
            printf(G_LEFT);
            for (int j = 0; j < (int) x; j++) printf("%-s", "····");
            printf("\b•");
        }
        else if (i <= (int) y)
        {
            printf(G_LEFT_P"%*c", (4 * x), ':');
            if (i > 0) 
            {
                printf(G_LEFT); printf("%*c", (4 * x), ':');
            }
            else printf("\n");
        }
    } 
    puts(G_BOTTOM_T);
    puts(G_BOTTOM_B);
}