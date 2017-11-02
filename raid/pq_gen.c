/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "raid.h"

#include <limits.h>
#include <stdint.h>

#if __WORDSIZE == 64 || _WIN64 || __x86_64__
# define notbit0 0xfefefefefefefefeULL
# define bit7    0x8080808080808080ULL
# define gf8poly 0x1d1d1d1d1d1d1d1dULL
#else
# define notbit0 0xfefefefeUL
# define bit7    0x80808080UL
# define gf8poly 0x1d1d1d1dUL
#endif

int pq_gen(int vects, int len, void **array)
{
	int i, j;
	unsigned long p, q, s;
	unsigned long **src = (unsigned long **)array;
	int blocks = len / sizeof(long);

	for (i = 0; i < blocks; i++) {
		q = p = src[vects - 3][i];

		for (j = vects - 4; j >= 0; j--) {
			p ^= s = src[j][i];
			q = s ^ (((q << 1) & notbit0) ^	// shift each byte
				 ((((q & bit7) << 1) - ((q & bit7) >> 7))	// mask out bytes
				  & gf8poly));	// apply poly
		}

		src[vects - 2][i] = p;	// second to last pointer is p
		src[vects - 1][i] = q;	// last pointer is q
	}
	return 0;
}
