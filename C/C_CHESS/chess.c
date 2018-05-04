/*
 * Copyright (c) 2018 Capobianco A.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "chess.h"

static Piece_d Knight =
{      .name_ID = "Kt"

,      .min_x_distance = 1
,      .max_x_distance = 2

,      .min_y_distance = 1
,      .max_y_distance = 2
};

static Piece_d King =
{      .name_ID = "K"

,      .min_x_distance = 1
,      .max_x_distance = 2

,      .min_y_distance = 1
,      .max_y_distance = 1
};

static Piece_d Pawn =
{      .name_ID = "P"

,      .min_x_distance = 0
,      .max_x_distance = 1

,      .min_y_distance = 1
,      .max_y_distance = 2
};

static Piece_d Queen =
{      .name_ID = "Q"

,      .min_x_distance = 1
,      .max_x_distance = 7

,      .min_y_distance = 1
,      .max_y_distance = 7
};

static Piece_d Bishop =
{      .name_ID = "B"

,      .min_x_distance = 0
,      .max_x_distance = 7

,      .min_y_distance = 0
,      .max_y_distance = 7
};

static Piece_d Rook =
{      .name_ID = "R"

,      .min_x_distance = 1
,      .max_x_distance = 7

,      .min_y_distance = 1
,      .max_y_distance = 7
};

static inline void
throw_fatal_error(char *func_name, int line)
{
        fprintf(stderr, "ERROR: %s failed in file : \'%s\' at line: %i", func_name, __FILE__, line);
        exit(EXIT_FAILURE);
}
#define fatal_error(x) throw_fatal_error(x, __LINE__)

static Set
make_Set(const bool is_white)
{
        static Set this;
        
        if (is_white)
        {

        }
}

static Piece*
make_Piece(const bool is_white)
{
        static Piece *this = NULL;
        if ((this = malloc(sizeof (Piece))) == NULL) fatal_error("malloc");
        
        this->is_white = is_white;

}


