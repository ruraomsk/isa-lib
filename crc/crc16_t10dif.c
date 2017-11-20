/*********************************************************************************
Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
    Функция вычисления контрольной суммы по стандарту Т10.
	uint16_t crc16_t10dif (uint16_t init_crc, const unsigned char *buf, uint64_t len);
 где:
	init_crc — начальное значение контрольной суммы для расчета;
	buf — указатель на массив для которого вычисляется контрольная сумма;
	len — размер массива в байтах.

    Алгоритм. 

Данная функция вычисляет контрольную сумму массива (с добавлением в качестве первого элемента init_crc)
нужного типа по стандарту Е10 с использованием полинома - 0x8bb7.
    Контрольная сумма выдаётся в качестве результата функции.
**********************************************************************************/
#include "crc.h"
#include <stdlib.h>
#define MAX_ITER 8

uint16_t crc16_t10dif(uint16_t seed, const unsigned char *bufer, uint64_t len) {
    register uint8_t *buf = (uint8_t *) bufer;
    register size_t rem = seed;
    register int j;

    register uint16_t poly = 0x8bb7; // t10dif standard

    while (len--) {
        rem = rem ^ (*buf++ << 8);
        j=MAX_ITER;
        while (j--) {
            rem = rem << 1;
            rem = (rem & 0x10000) ? rem ^ poly : rem;
        }
    }
    return rem;
}
