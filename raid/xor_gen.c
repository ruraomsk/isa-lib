#include "types.h"
#include <limits.h>
#include <stdint.h>

int xor_gen(int vects, int len, void **array)
{
    int i, j;
    if (vects < 3)
        return -1;
    if (!(len & (sizeof(unsigned long) - 1)))
    {
        // выровнено
        unsigned long *pSrc, *pRez, *tmp; //parity;
        unsigned long **src = (unsigned long **)array;
        len = len / sizeof(unsigned long);
        // перепишем первую строку в результат
        tmp = src[vects - 1];
        i = len;
        pSrc = src[0];
        pRez = tmp;
        while (i--)
            *pRez++ = *pSrc++;
         for (j = 1; j < vects - 1; j++)
        {
            pSrc = src[j];
            pRez = tmp;
            i = len;
            while (i--)
                *pRez++ ^= *pSrc++;
        }
        return 0;
    }

    unsigned char *pSrc, *pRez, *tmp; //parity;
    unsigned char **src = (unsigned char **)array;

    // перепишем первую строку в результат
    tmp = src[vects - 1];
    i = len;
    pSrc = src[0];
    pRez = tmp;
    while (i--)
        *pRez++ = *pSrc++;

    for (j = 1; j < vects - 1; j++)
    {
        pSrc = src[j];
        pRez = tmp;
        i = len;
        while (i--)
            *pRez++ ^= *pSrc++;
    }
    return 0;
}

