/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "crc.h"
#include <stdlib.h>
#define MAX_ITER 8

uint32_t crc32_gzip_refl(uint32_t seed, const unsigned char *bufer, uint64_t len) {
    uint8_t *buf = (uint8_t *) bufer;
    uint64_t rem = ~seed;
    int i, j;

    uint32_t poly = 0xEDB88320; // IEEE standard

    for (i = 0; i < len; i++) {
        rem = rem ^ (buf[i]);
        for (j = 0; j < MAX_ITER; j++) {
            rem = (rem & 0x1ULL) ? (rem >> 1) ^ poly : (rem >> 1);
        }
    }
    return ~rem;
}

