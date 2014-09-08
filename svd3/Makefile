.SUFFIXES: .c .u
CC= gcc
CFLAGS  = 
LDFLAGS = 



INCLUDES = -I$(CURDIR)/includes -I$(CURDIR)
COMPILE_C = $(CC) $(CFLAGS) -lm -O2 $(INCLUDES)
COMMON_SRC := $(wildcard $(CURDIR)/*.c)
C_SRC := $(wildcard $(CURDIR)/includes/*.c)
SMALL = 
MEDIUM =
LARGE =

all: small medium large

compile:
	gcc -lm main.c common/*.c $(C_SRC) svd.c svd2.c sortSVDResult.c

small:
	gcc -lm main.c common/*.c $(C_SRC) svd.c svd2.c sortSVDResult.c
	./a.out small.txt

medium:
	gcc -lm main.c common/*.c $(C_SRC) svd.c svd2.c sortSVDResult.c
	./a.out med.txt

large:
	gcc -lm main.c common/*.c $(C_SRC) svd.c svd2.c sortSVDResult.c
	./a.out large.txt

clean:
	-rm a.out
