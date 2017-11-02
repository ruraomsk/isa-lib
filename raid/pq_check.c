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

int pq_check(int vects, int len, void **array)
{
	int i, j;
	unsigned char p, q, s;
	unsigned char **src = (unsigned char **)array;

	for (i = 0; i < len; i++) {
		q = p = src[vects - 3][i];

		for (j = vects - 4; j >= 0; j--) {
			s = src[j][i];
			p ^= s;

			// mult by GF{2}
			q = s ^ ((q << 1) ^ ((q & 0x80) ? 0x1d : 0));
		}

		if (src[vects - 2][i] != p)	// second to last pointer is p
			return i | 1;
		if (src[vects - 1][i] != q)	// last pointer is q
			return i | 2;
	}
	return 0;
}


