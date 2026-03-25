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

void photonPrintTiming(unsigned int * elapsed)
{
    printf("Usecs elapsed\t\t- %u\n", elapsed[0]);
    for (int j = 0; j < PERF_CTR_NUM_BANKS; j++) {
        uint64_t delta = ((uint64_t)elapsed[1 + j*2 + 1] << 32) | elapsed[1 + j*2];
        printf("  bank %d: %llu\n", j, (unsigned long long)delta);
    }
    printf("\n");
}

/** End of C Code **/
