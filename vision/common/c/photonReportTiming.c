/********************************
Author: Sravanthi Kota Venkata
********************************/

/** C File **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include "timingUtils.h"
#include "sdvbs_common.h"

#define PERF_CTR_NUM_BANKS 8

unsigned int * photonReportTiming(unsigned int* startCycles,unsigned int* endCycles)
{
    unsigned int *elapsed = (unsigned int*)malloc(sizeof(unsigned int) * 17);
	elapsed[0] = (unsigned int)(endCycles[0] - startCycles[0]);
	for (int j = 0; j < PERF_CTR_NUM_BANKS; j++) {
		uint64_t start_val = ((uint64_t)startCycles[1 + j*2 + 1] << 32) | startCycles[1 + j*2];
		uint64_t end_val   = ((uint64_t)endCycles[1 + j*2 + 1]   << 32) | endCycles[1 + j*2];
		uint64_t delta = end_val - start_val;
		elapsed[1 + j*2]     = (uint32_t)(delta & 0xffffffff);
		elapsed[1 + j*2 + 1] = (uint32_t)(delta >> 32);
	}
    return elapsed;
}

/** End of C Code **/
