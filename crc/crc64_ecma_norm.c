/*********************************************************************************
Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
	Функция вычисления контрольной суммы стандарта ECMA-182.
	uint64_t crc64_ecma_norm (uint64_t init_crc, const unsigned char *buf, uint64_t len);
 где:
	init_crc — начальное значение контрольной суммы для расчета;
	buf — указатель на массив для которого вычисляется контрольная сумма;
	len — размер массива в байтах.

	Алгоритм. 

Данная функция вычисляет контрольную сумму массива (с добавлением в качестве первого элемента init_crc) 
нужного типа с использованием полинома стандарта ECMA-182 - 0x42F0E1EBA9EA3693ULL. 
Контрольная сумма выдаётся в качестве результата функции.
**********************************************************************************/
#include "crc.h"
#include "crc64.h"
#include <stdint.h>
#define MAX_ITER 8

uint64_t crc64_ecma_norm(uint64_t seed, const uint8_t *buf, uint64_t len)
{
	register uint64_t rem = ~seed;
	register unsigned int  j;

	register uint64_t poly = 0x42F0E1EBA9EA3693ULL; // ECMA-182 standard

	while( len--)
	{
		rem = rem ^ ((uint64_t)*buf++ << 56);
		j=MAX_ITER;
		while  (j--)
		{
			rem = (rem & 0x8000000000000000ULL ? poly : 0) ^ (rem << 1);
		}
	}
	return ~rem;
}
