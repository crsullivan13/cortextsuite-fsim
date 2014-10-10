# Top level makefile for CortexSuite (BETA)
# UCSD

all:
	small medium large

vision:
	make -C ${CURDIR}/vision/ c-run

small:
	make -C ${CURDIR}/cortex/* small

medium:
	make -C ${CURDIR}/cortex/* medium 

large:
	make -C ${CURDIR}/cortex/* large

cleanx:
	make -C ${CURDIR}/cortex/* clean
