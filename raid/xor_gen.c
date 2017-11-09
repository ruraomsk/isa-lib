#include "types.h"
#include <limits.h>
#include <stdint.h>

struct UINT256 {
    UINT64 p1;
    UINT64 p2;
    UINT64 p3;
    UINT64 p4;
};

int xor_gen(int vects, int len, void **array) {
    int i, j;
    if (vects < 3) return 1;
//    if (!(len & 31)) {
//        // выровнено 
//        struct UINT256 parity;
//        struct UINT256 **src = (struct UINT256 **) array;
//        len = len / sizeof (32);
//        for (i = 0; i < len; i++) {
//            parity = src[0][i];
//            for (j = 1; j < vects - 1; j++) {
//                parity.p1 ^= src[j][i].p1;
//                parity.p2 ^= src[j][i].p2;
//                parity.p3 ^= src[j][i].p3;
//                parity.p4 ^= src[j][i].p4;
//
//            }
//
//            src[vects - 1][i] = parity; // last pointer is dest
//        }
//        return 0;
//    }
    if (!(len & (sizeof (unsigned long) - 1))) {
        // выровнено 
        unsigned long parity;
        unsigned long **src = (unsigned long **) array;
        len = len / sizeof (unsigned long);
        for (i = 0; i < len; i++) {
            parity = src[0][i];
            for (j = 1; j < vects - 1; j++)
                parity ^= src[j][i];

            src[vects - 1][i] = parity; // last pointer is dest
        }
        return 0;
    }

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
