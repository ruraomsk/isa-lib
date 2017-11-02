/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "types.h"
#include <limits.h>
#include <stdint.h>
#include<stdio.h>

#if __WORDSIZE == 64 || _WIN64 || __x86_64__
#define notbit0 0xfefefefefefefefeULL
#define bit7    0x8080808080808080ULL
#define gf8poly 0x1d1d1d1d1d1d1d1dULL
#else
#define notbit0 0xfefefefeUL
#define bit7    0x80808080UL
#define gf8poly 0x1d1d1d1dUL
#endif

int xor_check(int vects, int len, void **array) {
    int i, j, fail = 0;
    if (vects < 3) return 1;
//    if (!(len & 7)) {
//        // выровнено по 8 байт
//        UINT64 parity, *pos;
//        UINT64 *src = (UINT64 **) array;
//        len = (len >> 8) + 1;
//        for (i = 0; i < len; i++) {
//            pos = src++;
//            parity = 0;
//            for (j = 0; j < vects; j++) {
//                parity ^= *pos;
//                pos += len;
//            }
//            if (parity != 0) {
//                fail = 1;
//                break;
//            }
//        }
//        if (fail && len > 0)
//            return len;
//        return fail;
//    }
    unsigned char parity;
    unsigned char **src = (unsigned char **) array;

    for (i = 0; i < len; i++) {
        parity = 0;
        for (j = 0; j < vects; j++)
            parity ^= src[j][i];

        if (parity != 0) {
            fail = 1;
            break;
        }
    }
    if (fail && len > 0)
        return len;
    return fail;
}

