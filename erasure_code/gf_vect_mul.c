/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <limits.h>
#include <string.h>  // for memset
#include "erasure_code.h"
#include "types.h"

int gf_vect_mul(int len, unsigned char *a, void *src, void *dest)
{
	//2nd element of table array is ref value used to fill it in
	unsigned char c = a[1];
        unsigned char *tsrc=(unsigned char *) src;
        unsigned char *tdest=(unsigned char *) dest;
        
	while (len-- > 0)
		*tdest++ = gf_mul(c, *tsrc++);
	return 0;
}

