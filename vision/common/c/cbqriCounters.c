/** C File **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "cbqriCounters.h"

/* Debugfs interface from cbqri-kern-module (cbqri_bandwidth.ko):
 *   bc_mon_ctl     write "<op> <mcid> <evt_id>", read "busy: ..\nstatus: ..\n"
 *   bc_mon_ctr_val read "value: ..\ninvalid: ..\noverflow: ..\n" */
#define CBQRI_DEBUGFS_DIR "/sys/kernel/debug/cbqri"

#define BC_OP_CONFIG 1 /* resets the MCID's counter and starts it counting */
#define BC_OP_READ   2 /* latches the MCID's counter into bc_mon_ctr */
#define BC_EVT_NONE      0
#define BC_EVT_READ_ONLY 2
#define BC_STATUS_OK     1

const char *const cbqriCounterNames[CBQRI_NUM_CTRS] = {
	"cache_bandwidth", /* reads from the cores into the LLC */
	"mem_bandwidth",   /* reads from the LLC out to DRAM */
};

static void cbqriOpen(int *fd, int ctrl, const char *file, int flags)
{
	char path[128];
	snprintf(path, sizeof(path), CBQRI_DEBUGFS_DIR "/%s/%s", cbqriCounterNames[ctrl], file);

	*fd = open(path, flags);
	if (*fd < 0) {
		perror(path);
		fprintf(stderr, "cbqri: needs root, debugfs mounted and cbqri_bandwidth.ko loaded\n");
		exit(1);
	}
}

static void cbqriReadFile(int ctrl, const char *file, char *buf, size_t len)
{
	int fd;
	cbqriOpen(&fd, ctrl, file, O_RDONLY);

	ssize_t n = read(fd, buf, len - 1);
	if (n < 0) {
		perror(file);
		exit(1);
	}
	buf[n] = '\0';
	close(fd);
}

static void cbqriMonCommand(int ctrl, int op, int evt)
{
	char buf[64];
	int fd;
	unsigned int status;
	char *field;

	int len = snprintf(buf, sizeof(buf), "%d %d %d", op, CBQRI_MCID, evt);
	cbqriOpen(&fd, ctrl, "bc_mon_ctl", O_WRONLY);
	if (write(fd, buf, len) != len) {
		perror("bc_mon_ctl");
		exit(1);
	}
	close(fd);

	cbqriReadFile(ctrl, "bc_mon_ctl", buf, sizeof(buf));
	field = strstr(buf, "status:");
	if (!field || sscanf(field, "status: %u", &status) != 1 || status != BC_STATUS_OK) {
		fprintf(stderr, "cbqri: %s op %d on mcid %d failed: %s\n",
			cbqriCounterNames[ctrl], op, CBQRI_MCID, buf);
		exit(1);
	}
}

void cbqriReadCounters(uint64_t *vals)
{
	/* The counters hold until configured, so start them on the first read.
	 * Later reads leave them running, so intervals can repeat. */
	static int started = 0;
	char buf[128];

	for (int j = 0; j < CBQRI_NUM_CTRS; j++) {
		unsigned long long value;
		unsigned int invalid, overflow;

		if (!started)
			cbqriMonCommand(j, BC_OP_CONFIG, BC_EVT_READ_ONLY);

		cbqriMonCommand(j, BC_OP_READ, BC_EVT_NONE);
		cbqriReadFile(j, "bc_mon_ctr_val", buf, sizeof(buf));
		if (sscanf(buf, "value: %llu invalid: %u overflow: %u", &value, &invalid, &overflow) != 3) {
			fprintf(stderr, "cbqri: bad %s counter output: %s\n", cbqriCounterNames[j], buf);
			exit(1);
		}
		if (invalid || overflow)
			fprintf(stderr, "cbqri: %s counter flagged invalid=%u overflow=%u\n",
				cbqriCounterNames[j], invalid, overflow);
		vals[j] = value;
	}
	started = 1;
}

/** End of C Code **/
