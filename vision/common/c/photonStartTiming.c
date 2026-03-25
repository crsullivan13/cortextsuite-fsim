/********************************
Author: Sravanthi Kota Venkata
********************************/

/** C File **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "timingUtils.h"
#include "sdvbs_common.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

#define PERF_CTR_PHYS_BASE   0x21000038ULL
#define PERF_CTR_NUM_BANKS   8
#define PERF_CTR_BANK_STRIDE 8
#define PERF_CTR_DOMAIN      1

unsigned int usecsStart()
{
	struct timeval         time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 +	time.tv_usec);
}

static void read_perf_ctrs(uint64_t *vals)
{
	uint64_t phys = PERF_CTR_PHYS_BASE + (uint64_t)PERF_CTR_DOMAIN * PERF_CTR_NUM_BANKS * PERF_CTR_BANK_STRIDE;
	long pagesz = sysconf(_SC_PAGE_SIZE);
	off_t page_base = (off_t)(phys & ~(uint64_t)(pagesz - 1));
	size_t page_off = (size_t)(phys - (uint64_t)page_base);
	size_t map_size = page_off + PERF_CTR_NUM_BANKS * PERF_CTR_BANK_STRIDE;

	int fd = open("/dev/mem", O_RDONLY | O_SYNC);
	if (fd < 0) { perror("open /dev/mem"); return; }

	volatile uint64_t *map = (volatile uint64_t *)mmap(NULL, map_size, PROT_READ, MAP_SHARED, fd, page_base);
	close(fd);
	if (map == MAP_FAILED) { perror("mmap /dev/mem"); return; }

	volatile uint64_t *ctrs = (volatile uint64_t *)((char *)map + page_off);
	for (int j = 0; j < PERF_CTR_NUM_BANKS; j++)
		vals[j] = ctrs[j];

	munmap((void *)map, map_size);
}

unsigned int* photonStartTiming()
{
	/* array[0]        = usecs
	 * array[1+j*2]   = bank j counter lo
	 * array[1+j*2+1] = bank j counter hi
	 * total: 1 + 8*2 = 17 elements */
	unsigned int *array = (unsigned int*)malloc(sizeof(unsigned int) * 17);

	array[0] = usecsStart();
	uint64_t banks[PERF_CTR_NUM_BANKS];
	read_perf_ctrs(banks);
	for (int j = 0; j < PERF_CTR_NUM_BANKS; j++) {
		array[1 + j*2]     = (uint32_t)(banks[j] & 0xffffffff);
		array[1 + j*2 + 1] = (uint32_t)(banks[j] >> 32);
	}
	return array;
}

/** End of C Code **/
