CC ?= gcc
CFLAGS = -Wall -fPIC
LIBS = blas/blas.a
SHVER = 1
OS = $(shell uname)


INCLUDES = -I$(CURDIR)/includes -I$(CURDIR)
COMPILE_C = $(CC) $(CFLAGS) -lm -O2 $(INCLUDES)
COMMON_SRC := $(wildcard $(CURDIR)/*.c)
C_SRC := $(wildcard $(CURDIR)/includes/*.c)

#LIBS = -lblas

all: train predict

small: $(C_SRC) $(LIBS)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(LIBS) $(CFLAGS) -o train-small
	./train-small ../data/100M/crime_scale

medium: $(C_SRC) $(LIBS)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(LIBS) $(CFLAGS) -o train-medium
	./train-medium ../data/10B/epsilon

large: $(C_SRC) $(LIBS)
	$(COMPILE_C) $(COMMON_SRC) $(C_SRC) $(LIBS) $(CFLAGS) -o train-large
	./train-large ../data/100B/kdda

blas/blas.a: blas/*.c blas/*.h
	make -C blas OPTFLAGS='$(CFLAGS)' CC='$(CC)'

clean:
	make -C blas clean
	rm -f *~ tron.o linear.o train predict liblinear.so.$(SHVER) train-small train-medium train-large
