# Top level makefile for CortexSuite (BETA)
# UCSD
#
#

subdirs = lda liblinear motion-estimation pca rbm sphinx srr svd3

vision:
	make -C ${CURDIR}/vision/ c-run

run-all: run-small run-medium run-large

compile:
	for dir in $(subdirs); do\
		$(MAKE) -C cortex/$$dir compile;\
		done
	
run-small:
	for dir in $(subdirs); do\
		$(MAKE) -C cortex/$$dir run-small;\
		done

run-medium:
	for dir in $(subdirs); do\
		$(MAKE) -C cortex/$$dir run-medium;\
		done
	
run-large:
	for dir in $(subdirs); do\
		$(MAKE) -C cortex/$$dir run-large;\
		done
	
clean:
	for dir in $(subdirs); do\
		$(MAKE) -C cortex/$$dir clean;\
		done
	
