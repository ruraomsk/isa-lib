/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "erasure_code.h"
#include "types.h"

void ec_encode_data_update(int len, int k, int rows, int vec_i, unsigned char *v,
        unsigned char *data, unsigned char **dest) {
    int i, l;
    unsigned char s;

    for (l = 0; l < rows; l++) {
        for (i = 0; i < len; i++) {
            s = dest[l][i];
            s ^= gf_mul(data[i], v[vec_i * 32 + l * k * 32 + 1]);

            dest[l][i] = s;
        }
    }
}
