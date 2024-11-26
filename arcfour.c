/* arcfour.c */
#include "arcfour.h"    // including arcfour header file

// rc4 initialization function to initialize rc4 state with a given key
Arcfour *rc4init(int8 *key, int16 ksize) {

    int8 tmp;
    // memory allocation for Arcfour structure
    Arcfour *p = (Arcfour*)malloc(sizeof(Arcfour));
    if (p == NULL) return NULL;
    
    // KSA (key scheduling algorithm)
    for (int i = 0; i < 256; i++)
        p->s[i] = i;
    p->i = p->j = p->k = 0;
    for (int i = 0; i < 256; i++){
        p->j = (p->j + p->s[i] + key[i % ksize]) % 256;
        tmp = p->s[p->j];
        p->s[p->j] = p->s[i];
        p->s[i] = tmp;
    }

    // init i, j, k of Arcfour with 0
    p->i = p->j = p->k = 0;

    // return initialized state
    return p;
}

// rc4byte function to generate a single byte of pseudo-random data using the rc4 algorithm
int8 rc4byte(Arcfour *p) {
    int16 tmp, tmp2;
    p->i = p->j = p->k = 0;

    p->i = (p->i + 1) % 256;
    p->j = (p->j + p->s[p->i]) % 256;

    tmp = p->s[p->j];
    p->s[p->j] = p->s[p->i];
    p->s[p->i] = tmp;

    tmp2 = (p->s[p->i] + p->s[p->j]) % 256;
    p->k = p->s[tmp2];

    // return the pseudo-random byte generated
    return p->k;
}

// rc4encrypt function to encrypt (or decrypt) a given text using rc4 algorithm
int8 *rc4encrypt(Arcfour *p, int8 *clear_text, int16 size) {
    int16 x;
    int8 *cipher_text = (int8*)malloc(size + 1);

    for (x = 0; x < size; x++)
        cipher_text[x] = clear_text[x] ^ rc4byte(p);
    
    return cipher_text;
}

// function to print binary data in hexadecimal format
void printbin(int8 *bin, const int16 size) {
    int16 i;
    int8 *p;

    assert(size > 0);

    for (i = size, p = bin; i; i--, p++) {
        if ((i % 2) == 0)
            printf(" ");
        printf("%.02x", *p);
    }
    putchar(10);
    return;
}