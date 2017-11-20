/*********************************************************************************
Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
	Функция вычисления контрольной суммы по коэффициенту 
        «Джонсона» с инверсией.
	uint64_t crc64_jones_refl (uint64_t init_crc, const unsigned char *buf, uint64_t len);
 где:
	init_crc — начальное значение контрольной суммы для расчета;
	buf — указатель на массив для которого вычисляется контрольная сумма;
	len — размер массива в байтах.

	Алгоритм. 

Данная функция вычисляет контрольную сумму массива (с добавлением в качестве первого элемента init_crc)
 нужного типа по коэффициенту «Джонсона» - с полиномом 0x95ac9329ac4bc9b5ULL. 
 Контрольная сумма инвертируется и выдаётся в качестве результата функции
**********************************************************************************/

#include "crc.h"
#include "crc64.h"
#include <stdint.h>
#define MAX_ITER	8

uint64_t crc64_jones_refl(uint64_t seed, const uint8_t * buf, uint64_t len)
{
	register uint64_t rem = ~seed;
	register int j;

	register uint64_t poly = 0x95ac9329ac4bc9b5ULL;	// Jones coefficients reflected

	while (len--) {
		rem = rem ^ (uint64_t) *buf++;
		j=MAX_ITER;
		while (j--) {
			rem = (rem & 0x1ULL ? poly : 0) ^ (rem >> 1);
		}
	}
	return ~rem;
}

