/*********************************************************************************
Библиотека функций быстрого доступа к данным для архитектуры «Эльбрус» («ЭЛЬФ»)
**********************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#ifdef __cplusplus
extern "C" {
#endif

// Use sys/time.h functions for time
#if defined (__unix__) || (__APPLE__) || (__MINGW32__)
# include <sys/time.h>
#endif

#ifdef _MSC_VER
# define inline __inline
# include <time.h>
# include <Windows.h>
#endif

#include <stdio.h>
#include <stdint.h>

struct perf{
	struct timeval tv;
};


#if defined (__unix__) || (__APPLE__) || (__MINGW32__)
static inline int perf_start(struct perf *p)
{
	return gettimeofday(&(p->tv), 0);
}
static inline int perf_stop(struct perf *p)
{
	return gettimeofday(&(p->tv), 0);
}

static inline void perf_print(struct perf stop, struct perf start, long long dsize)
{
	long long secs = stop.tv.tv_sec - start.tv.tv_sec;
	long long usecs = secs * 1000000 + stop.tv.tv_usec - start.tv.tv_usec;

	printf("runtime = %10lld usecs", usecs);
	if (dsize != 0) {
		printf(", bandwidth %lld MB in %.4f sec = %.2f MB/s\n", dsize/(1024*1024),
			((double) usecs)/1000000, ((double) dsize) / (double)usecs);
	}
	else
		printf("\n");
}
#endif

static inline uint64_t get_filesize(FILE *fp)
{
	uint64_t file_size;
	fpos_t pos, pos_curr;

	fgetpos(fp, &pos_curr);  /* Save current position */
	fseeko(fp, 0, SEEK_END);
	fgetpos(fp, &pos);
	file_size = *(uint64_t *)&pos;
	fsetpos(fp, &pos_curr);  /* Restore position */

	return file_size;
}

#ifdef __cplusplus
}
#endif

#endif // _TEST_H
