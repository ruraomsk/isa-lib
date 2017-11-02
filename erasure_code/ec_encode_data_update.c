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

void ec_encode_data_update(int len, int k, int rows, int vec_i, unsigned char *v,
        unsigned char *data, unsigned char **dest) {
    int i, l;
    unsigned char s;
    unsigned char ss,a,b;
    int ii;

    for (l = 0; l < rows; l++) {
        for (i = 0; i < len; i++) {
            s = dest[l][i];
            a = data[i];
            b = v[vec_i * 32 + l * k * 32 + 1];
            if ((a == 0) || (b == 0)) ss = 0;
            else ss = gff_base[(ii = gflog_base[a] + gflog_base[b]) > 254 ? ii - 255 : ii];
            s ^= ss;
            dest[l][i] = s;
        }
    }
}
