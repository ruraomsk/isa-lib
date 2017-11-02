/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "crc.h"
#include "crc64.h"
#include <stdint.h>

#define MAX_ITER	8

uint64_t crc64_ecma_refl(uint64_t seed, const uint8_t * buf, uint64_t len)
{
	uint64_t rem = ~seed;
	unsigned int i, j;

	uint64_t poly = 0xC96C5795D7870F42ULL;	// ECMA-182 standard reflected

	for (i = 0; i < len; i++) {
		rem = rem ^ (uint64_t) buf[i];
		for (j = 0; j < MAX_ITER; j++) {
			rem = (rem & 0x1ULL ? poly : 0) ^ (rem >> 1);
		}
	}
	return ~rem;
}
