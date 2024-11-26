/* arcfour.h */
#ifndef ARCFOUR_H
#define ARCFOUR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define export                  __attribute__((visibility("default")))
#define rc4decrypt(x, y, z)     rc4encrypt(x, y, z)
#define rc4uninit(x)            free(x)

typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;

typedef struct {
    int16 i, j, k;
    int8 s[256];
} Arcfour;

export Arcfour *rc4init(int8*, int16);
export int8 rc4byte(Arcfour*);
export int8 *rc4encrypt(Arcfour*, int8*, int16);
export void printbin(int8*, const int16);

#endif
