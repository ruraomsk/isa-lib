/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "crc.h"
#include <stdlib.h>
#define MAX_ITER 8

uint32_t crc32_ieee(uint32_t seed, const unsigned char *bufer, uint64_t len) {
    uint8_t *buf = (uint8_t *) bufer;
    uint64_t rem = ~seed;
    unsigned int i, j;

    uint32_t poly = 0x04C11DB7; // IEEE standard

    for (i = 0; i < len; i++) {
        rem = rem ^ (buf[i] << 24);
        for (j = 0; j < MAX_ITER; j++) {
            rem = rem << 1;
            rem = (rem & 0x100000000ULL) ? rem ^ poly : rem;
        }
    }
    return ~rem;
}

