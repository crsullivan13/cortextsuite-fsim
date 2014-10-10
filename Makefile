# Top level makefile for CortexSuite (BETA)
# UCSD

all:
	small meidum large

small:
	make -C ${CURDIR}* small

medium:
	make -C ${CURDIR}* medium

large:
	make -C ${CURDIR}* large

clean:
	make -C pca/ clean
	make -C lda/ clean
	make -C liblinear/ clean
	make -C motion-estimation/ clean
	make -C rbm/ clean
	make -C sphinx/ clean
	make -C srr/ clean
	make -C svd3/ clean
	
