/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "crc.h"
#include <stdlib.h>
#define MAX_ITER 8

uint16_t crc16_t10dif(uint16_t seed, const unsigned char *bufer, uint64_t len) {
    uint8_t *buf = (uint8_t *) bufer;
    size_t rem = seed;
    unsigned int i, j;

    uint16_t poly = 0x8bb7; // t10dif standard

    for (i = 0; i < len; i++) {
        rem = rem ^ (buf[i] << 8);
        for (j = 0; j < MAX_ITER; j++) {
            rem = rem << 1;
            rem = (rem & 0x10000) ? rem ^ poly : rem;
        }
    }
    return rem;
}
