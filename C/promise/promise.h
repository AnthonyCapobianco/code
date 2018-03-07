/* 
 * This project falls under the JustDontUseItForDeviousPurposes License.
 * Any use of the promise.h header with the intent to annoy and/or
 * cause physical and/or psychological harm to anyone, including but not limited to,
 * yourself and/or other forms of life is STRICTLY prohibited.
 * Otherwise do whatever you want with it, just don't blame me afterwards.
 *
 * Note that this license only applies this project and doesn't extend to other software/library used.
 */
#include <stdio.h>

#ifndef _PROMISE_H_INCLUDED_
#define _PROMISE_H_INCLUDED_

enum _Promise_State { FALSE, TRUE } Promise_State;

#ifndef promise_t

typedef enum _Promise_State promise_t;

#endif

typedef struct _Promise_Char
{       char obj;
        promise_t promise;
} Promise_Char;

typedef struct _Promise_Char_Ptr
{       char *obj;
        promise_t promise;
} Promise_Char_Ptr;

typedef struct _Promise_Int
{       int obj;
        promise_t promise;
} Promise_Int;

typedef struct _Promise_Long
{       long obj;
        promise_t promise;
} Promise_Long;

typedef struct _Promise_Float
{       float obj;
        promise_t promise;
} Promise_Float;

typedef struct _Promise_Double
{       double obj;
        promise_t promise;
} Promise_Double;

#endif 
