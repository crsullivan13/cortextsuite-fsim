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

void photonPrintTiming(unsigned int * elapsed)
{
    printf("Usecs elapsed\t\t- %u\n", elapsed[0]);
    for (int j = 0; j < CBQRI_NUM_CTRS; j++) {
        uint64_t delta = ((uint64_t)elapsed[1 + j*2 + 1] << 32) | elapsed[1 + j*2];
        printf("  %s mcid %d: %llu\n", cbqriCounterNames[j], CBQRI_MCID, (unsigned long long)delta);
    }
    printf("\n");
}

/** End of C Code **/
