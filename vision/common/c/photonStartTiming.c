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
#include "cbqriCounters.h"

#include <sys/time.h>
#include <stdint.h>

unsigned int usecsStart()
{
	struct timeval         time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 +	time.tv_usec);
}

unsigned int* photonStartTiming()
{
	unsigned int *array = (unsigned int*)malloc(sizeof(unsigned int) * PHOTON_TIMING_WORDS);

	array[0] = usecsStart();
	uint64_t ctrs[CBQRI_NUM_CTRS];
	cbqriReadCounters(ctrs);
	for (int j = 0; j < CBQRI_NUM_CTRS; j++) {
		array[1 + j*2]     = (uint32_t)(ctrs[j] & 0xffffffff);
		array[1 + j*2 + 1] = (uint32_t)(ctrs[j] >> 32);
	}
	return array;
}

/** End of C Code **/
