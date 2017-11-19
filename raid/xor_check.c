/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "types.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int xor_check(int vects, int len, void **array)
{
    int i, j, fail = 0;
    if (vects < 3)
        return -1;
    if (!(len & (sizeof(unsigned long) - 1)))
    {
        // выровнено
        unsigned long parity;
        unsigned long **src = (unsigned long **)array;
        len = len / sizeof(unsigned long);
        parity = 0;
        for (i = 0; i < len; i++)
        {
            for (j = 0; j < vects; j++)
                parity ^= src[j][i];
            if (parity != 0)
            {
                fail = i + 1;
                break;
            }
        }
        return fail;
    }

    unsigned char parity;
    unsigned char **src = (unsigned char **)array;

    for (i = 0; i < len; i++)
    {
        parity = 0;
        for (j = 0; j < vects; j++)
            parity ^= src[j][i];

        if (parity != 0)
        {
            fail = i + 1;
            break;
        }
    }
    return fail;
}
