/*
 * Функция производит операцию XOR над массивов векторов
 * последний векто в массиве приемный вектор
 * 
 */
#include "types.h"
#include <limits.h>
#include <stdint.h>

int xor_gen(int vects, int len, void **array) {
    int i, j;
    if (vects < 3) return 1;

//    if (!(len & 7)) {
//        // выровнено по 8 байт
//        UINT64 parity;
//        unsigned char *src = (unsigned char *) array;
//        unsigned char *tmp = (unsigned char *) array;
//        unsigned char *dst = (src + (vects - 1) * len);
//        int lenght = len;
//        len = len >> 8;
//        for (i = 0; i < len; i++) {
//            parity = *src;
//            tmp = src + lenght;
//            for (j = 1; j < vects - 1; j++) {
//                parity ^= *tmp;
//                tmp += lenght;
//            }
//            *dst = parity;
//            dst += sizeof (UINT64);
//            src += sizeof (UINT64);
//        }
//        return 0;
//
//    }
    unsigned char parity;
    unsigned char **src = (unsigned char **) array;

    for (i = 0; i < len; i++) {
        parity = src[0][i];
        for (j = 1; j < vects - 1; j++)
            parity ^= src[j][i];

        src[vects - 1][i] = parity; // last pointer is dest

    }

    return 0;
}
