/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_MSG_RET_NULL(x) fprintf(stderr, "ERROR: %s returned NULL in file '%s' at line: %i.", x, __FILE__, __LINE__)

static inline long double get_souls_to_level_up(long double);
static inline long double get_long_double_from_stdin(const char *restrict);

int main(void)
{
        long double user_level = get_long_double_from_stdin("Please insert your current level: ");

        const char *want = "Please insert the level you want to reach: ";
        long double wanted_level = get_long_double_from_stdin(want);
        long double diff_level = (wanted_level > user_level) ? user_level : 0.0L;
        
        long double souls_to_level_up = diff_level * get_souls_to_level_up(user_level);
        
        printf("You'll need %lli souls to level up to level %lli", llrintl(souls_to_level_up), llrintl(wanted_level));
        
}

static inline long double
get_souls_to_level_up(long double lvl)
{
        return (((lvl * lvl * lvl) * 0.02L) + ((lvl * lvl) * 3.06L) + (lvl * 105.6L)) - 895.0L;
}

static inline long double
get_long_double_from_stdin(const char *restrict ask)
{
        printf("%s", ask);
        
        char s[5] = "";
        if (fgets(s, 5, stdin) == NULL)
        {
                ERROR_MSG_RET_NULL("fgets");
                exit(EXIT_FAILURE);
        }
        
        /* Remove \n from fgets */
        char *check_ptr = strchr(s, '\n');
        if (check_ptr) *check_ptr = '\0';
        
        char *end_ptr = NULL;
        return strtold(s, &end_ptr);
}
