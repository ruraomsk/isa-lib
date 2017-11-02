/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "types.h"

void ec_encode_data(int len, int srcs, int dests, unsigned char *v,
        unsigned char **src, unsigned char **dest) {
    int i, j, l;
    unsigned char s;

    for (l = 0; l < dests; l++) {
        for (i = 0; i < len; i++) {
            s = 0;
            for (j = 0; j < srcs; j++)
                s ^= gf_mul(src[j][i], v[j * 32 + l * srcs * 32 + 1]);

            dest[l][i] = s;
        }
    }
}

