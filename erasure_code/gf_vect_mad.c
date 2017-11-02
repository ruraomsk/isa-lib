/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "erasure_code.h"
#include "types.h"

void gf_vect_mad(int len, int vec, int vec_i,
        unsigned char *v, unsigned char *src, unsigned char *dest) {
    int i;
    unsigned char s;
    for (i = 0; i < len; i++) {
        s = dest[i];
        s ^= gf_mul(src[i], v[vec_i * 32 + 1]);
        dest[i] = s;
    }
}

