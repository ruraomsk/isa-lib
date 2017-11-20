/*
            Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
  Функция проверки массива векторов на XOR
Вызов:
            	int xor_check (int vects, int len, void **array);
 где:
	vects — кол-во векторов источников и один вектор результата;
	len — длина каждого вектора в байтах;
	array — массив указателей на вектора источников и вектор результата. 

    Алгоритм:
Для каждой «колонки» вычисляется значение «суммы» по формуле
V0[k] = V1 [k] ^ V2 [k] ^ …^ Vn [k]
   где: Vi [k] – элементы векторов массива array (i = 1, n);
             n = len;
            V0[k] – результат «суммирования».
            ^ - операция xor, выполняемая над векторами поэлементно.
Для повышения скорости работы функции рекомендуется использовать длину массивов векторов кратной 32 байтам.
Данная функция возвращает 0 в случае, если результаты V0[k] для всех колонок равны 0.
Функция возвращает -1 в случае, если vects – (количество векторов) меньше 3.
Как только вычисление результата для k-й колонки даст не 0, то функция возвращает номер колонки (начиная с 1).
Значение выхода k больше нуля сигнализирует о наличии ошибок в k-й колонке массива.
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
