/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "erasure_code.h"
#include "types.h"

void gf_vect_dot_prod(int len, int vlen, unsigned char *v,
		      unsigned char **src, unsigned char *dest)
{
	int i, j;
	unsigned char s;
	for (i = 0; i < len; i++) {
		s = 0;
		for (j = 0; j < vlen; j++)
			s ^= gf_mul(src[j][i], v[j * 32 + 1]);

		dest[i] = s;
	}
}

