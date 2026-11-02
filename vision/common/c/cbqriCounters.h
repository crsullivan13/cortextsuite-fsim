#ifndef _CBQRI_COUNTERS_
#define _CBQRI_COUNTERS_

#include <stdint.h>

/* MCID whose counters are reported. The core running the benchmark must be
 * tagged with it, e.g. for cpu0 with MCID 1 and RCID 1 (srmcfg bits [21:16] are
 * the MCID, the value is parsed as hex):
 *     echo 0 10001 > /sys/kernel/debug/cbqri/per_cpu_srmcfg
 * Override at build time with CFLAGS=-DCBQRI_MCID=<n>. */
#ifndef CBQRI_MCID
#define CBQRI_MCID 1
#endif

/* One counter per CBQRI bandwidth controller */
#define CBQRI_NUM_CTRS 2

/* Timing array layout, shared by the photon*Timing functions:
 * array[0]       = usecs
 * array[1+j*2]   = counter j lo
 * array[1+j*2+1] = counter j hi */
#define PHOTON_TIMING_WORDS (1 + CBQRI_NUM_CTRS * 2)

extern const char *const cbqriCounterNames[CBQRI_NUM_CTRS];

/* Reads each controller's counter for CBQRI_MCID. Exits on failure. */
void cbqriReadCounters(uint64_t *vals);

#endif
