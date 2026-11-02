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
#include "cbqriCounters.h"

unsigned int * photonReportTiming(unsigned int* startCycles,unsigned int* endCycles)
{
    unsigned int *elapsed = (unsigned int*)malloc(sizeof(unsigned int) * PHOTON_TIMING_WORDS);
	elapsed[0] = (unsigned int)(endCycles[0] - startCycles[0]);
	for (int j = 0; j < CBQRI_NUM_CTRS; j++) {
		uint64_t start_val = ((uint64_t)startCycles[1 + j*2 + 1] << 32) | startCycles[1 + j*2];
		uint64_t end_val   = ((uint64_t)endCycles[1 + j*2 + 1]   << 32) | endCycles[1 + j*2];
		uint64_t delta = end_val - start_val;
		elapsed[1 + j*2]     = (uint32_t)(delta & 0xffffffff);
		elapsed[1 + j*2 + 1] = (uint32_t)(delta >> 32);
	}
    return elapsed;
}

/* Adds one interval from photonReportTiming into a running total */
void photonAccumulateTiming(unsigned int* total, unsigned int* interval)
{
	total[0] += interval[0];
	for (int j = 0; j < CBQRI_NUM_CTRS; j++) {
		uint64_t sum = (((uint64_t)total[1 + j*2 + 1] << 32) | total[1 + j*2])
		             + (((uint64_t)interval[1 + j*2 + 1] << 32) | interval[1 + j*2]);
		total[1 + j*2]     = (uint32_t)(sum & 0xffffffff);
		total[1 + j*2 + 1] = (uint32_t)(sum >> 32);
	}
}

/** End of C Code **/
