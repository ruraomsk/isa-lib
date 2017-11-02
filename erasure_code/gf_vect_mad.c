/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "types.h"

extern unsigned char gff_base[];
extern unsigned char gflog_base[];

void gf_vect_mad(int len, int vec, int vec_i,
        unsigned char *v, unsigned char *src, unsigned char *dest) {
    int i,ii;
    unsigned char s;
        unsigned char ss,a,b;

    for (i = 0; i < len; i++) {
        s = dest[i];
            a = src[i];
            b = v[vec_i * 32 + 1];
            if ((a == 0) || (b == 0)) ss = 0;
            else ss = gff_base[(ii = gflog_base[a] + gflog_base[b]) > 254 ? ii - 255 : ii];

        s ^= ss;
        dest[i] = s;
    }
}

