.SUFFIXES: .c .u
.PHONY: all small medium large clean

TOP_DIR = $(shell pwd)
COMMON = $(TOP_DIR)/common

CC= gcc
CFLAGS  = -O2
LDFLAGS = -lm



#INCLUDES = -I$(CURDIR) -I/home/shelbyt/Documents/benchmarks/common 
INCLUDES = -I$(CURDIR)

COMPILE_C = $(CC) $(CFLAGS) -lm -O2 $(INCLUDES)
COMMON_SRC := $(wildcard $(CURDIR)/*.c)
#C_SRC := $(wildcard /home/shelbyt/Documents/benchmarks/common/*.c)
C_SRC := $(wildcard $(COMMON)/*.c)


all: small medium large

small: $(C_SRC)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(CFLAGS) -o lda-small
	./lda-small est .1 3 settings.txt small/small_data.dat random small/results

medium: $(C_SRC)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(CFLAGS) -o lda-medium
	./lda-medium est .1 3 settings.txt medium/medium_data.dat random medium/results

large: $(C_SRC)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(CFLAGS) -o lda-large
	./lda-large est .1 3 settings.txt large/large_data.dat random large/results


clean:
	-rm -f *.o lda-small lda-medium lda-large
