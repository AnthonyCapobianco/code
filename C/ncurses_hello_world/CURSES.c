/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

int 
main(void) 
{
        /* Initialize stdscr */
        initscr();
        /* Let control keys break (to quit the app) */
        /* cbreak(); */
        raw();
        /* If we don't want that, use `raw();` instead */
        
        /* Print to window */
        int a = 0;
        /* Just so the window doesn't close. (I don't like it either) */
        while (a != 10) printf("%d\n", (a = getch()));
        
        
        /* Free the windows object */
        endwin();
        
        /* Anyway I don't like it so I'll do it myself. */
		  
        return 0;
}
