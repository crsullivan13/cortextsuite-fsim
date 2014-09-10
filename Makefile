all:
	small meidum large

small:
	make -C pca/ small
	make -C lda/ small
	make -C liblinear/ small
	make -C motion-estimation/ small
	make -C rbm/ small
	make -C sphinx/ small
	make -C srr/ small
	make -C svd3/ small

medium:
	make -C pca/ medium
	make -C lda/ medium
	make -C liblinear/ medium
	make -C motion-estimation/ medium
	make -C rbm/ medium
	make -C sphinx/ medium
	make -C srr/ medium
	make -C svd3/ medium

large:
	make -C pca/ large
	make -C lda/ large
	make -C liblinear/ large
	make -C motion-estimation/ large
	make -C rbm/ large
	make -C sphinx/ large
	make -C srr/ large
	make -C svd3/ small

clean:
	make -C pca/ clean
	make -C lda/ clean
	make -C liblinear/ clean
	make -C motion-estimation/ clean
	make -C rbm/ clean
	make -C sphinx/ clean
	make -C srr/ clean
	make -C svd3/ clean


