/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "erasure_code.h"
#include "types.h"

extern unsigned char gff_base[];
extern unsigned char gflog_base[];

int gf_vect_mul(int len, unsigned char *a, void *src, void *dest) {
    //2nd element of table array is ref value used to fill it in
    unsigned char c = a[1];
    unsigned char *tsrc = (unsigned char *) src;
    unsigned char *tdest = (unsigned char *) dest;
    unsigned char ss, aa, b;
    int ii;
    while (len-- > 0) {
        aa = c;
        b = *tsrc++;
        if ((aa == 0) || (b == 0)) ss = 0;
        else ss = gff_base[(ii = gflog_base[aa] + gflog_base[b]) > 254 ? ii - 255 : ii];

        *tdest++ = ss;

    }
    return 0;
}

