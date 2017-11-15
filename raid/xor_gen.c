#include "types.h"
#include <limits.h>
#include <stdint.h>

int xor_gen(int vects, int len, void **array) {
    int i, j;
    if (vects < 3) return 1;
    if (!(len & (sizeof (unsigned long) - 1))) {
        // выровнено
        unsigned long *pSrc, *pRez, *tmp; //parity;
        unsigned long **src = (unsigned long **) array;
        len = len / sizeof (unsigned long);
        // перепишем первую строку в результат
        tmp = src[vects - 1];
        for (pSrc = src[0], pRez = tmp, i = 0; i < len; i++, pSrc++, pRez++)
            *pRez = *pSrc;
        //       xor  по строкам
        for (j = 1; j < vects - 1; j++)
            for (pSrc = src[j], pRez = tmp, i = 0; i < len; i++, pSrc++, pRez++)
                *pRez ^= *pSrc;
        return 0;
    }

    unsigned char *pSrc, *pRez, *tmp; //parity;
    unsigned char **src = (unsigned char **) array;

    tmp = src[vects - 1];
    for (pSrc = src[0], pRez = tmp, i = 0; i < len; i++, pSrc++, pRez++)
        *pRez = *pSrc;
    //       xor  по строкам
    for (j = 1; j < vects - 1; j++)
        for (pSrc = src[j], pRez = tmp, i = 0; i < len; i++, pSrc++, pRez++)
            *pRez ^= *pSrc;
    return 0;
}
