/*
            Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
Функция создания результирующего вектора  по исключающему ИЛИ.
Вызов:
	int xor_gen(int vects, int len, void **array);
 где:
	vects — кол-во векторов источников и один вектор результата;
	len — длина каждого вектора в байтах;
	array — массив указателей на вектора источников и вектор результата. 

    Алгоритм:
Вычисляется вектор результата по формуле
P = V1 ^ V2 ^ …^ Vn 
   где: Vi - вектора - источники (i = 1, n);
             n = vects-1;
            P – вектор результата.
            ^ - операция xor, выполняемая над векторами поэлементно.
Вектор результата помещается последним в массиве array. 
Для повышения скорости работы функции рекомендуется использовать длину массивов векторов кратной 32 байтам. 
Данная функция возвращает: 0 в случае нормального завершения и -1, если vects – (количество векторов) меньше 3.
*/

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
            pSrc = *(++src);
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
        pSrc = *(++src);
        pRez = tmp;
        i = len;
        while (i--)
            *pRez++ ^= *pSrc++;
    }
    return 0;
}
