# Top level makefile for CortexSuite (BETA)
# UCSD

all:
	small medium large

small:
	make -C ${CURDIR}/cortex/* small

medium:
	make -C ${CURDIR}/cortex/* medium 

large:
	make -C ${CURDIR}/cortex/* large

clean:
	make -C pca/ clean
	make -C lda/ clean
	make -C liblinear/ clean
	make -C motion-estimation/ clean
	make -C rbm/ clean
	make -C sphinx/ clean
	make -C srr/ clean
	make -C svd3/ clean
	
