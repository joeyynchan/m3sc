GCC=gcc
BASIC_SOURCE=MakeWpowers.c FastSINE.c info.c FastDFS.c FastDFT.c
FT1=FastTransform.c
FT2=FastTransform_v2.c
COMPARE_DFS=FastDFS_copy.c FastTransform_v2_copy.c
FASTSINE2=FastSINE2D.c
FASTSINE3=FastSINE3D.c
MATMUL=Matmul.c
MATMULC=MatmulC.c
CUBE=Cube.c
OUTPUT=main.out
CFLAGS=-g -ansi -pedantic -Wall -O3 -march=native -mfpmath=sse -funroll-loops

all:

main: $(BASIC_SOURCE) $(FAST1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_check_FastDFS: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_check_FastDFS2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) main_check_FastDFS.c $^ -o $(OUTPUT)

main_speed_FastDFS: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_speed_FastDFS2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) main_speed_FastDFS.c $^ -o $(OUTPUT)

main_test_FastDFS: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_test_FastDFS2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) main_test_FastDFS.c $^ -o $(OUTPUT)

main_compare_FastDFS: $(BASIC_SOURCE) $(FT2) $(MATMULC) $(COMPARE_DFS)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)




main_check_FastDFT: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_check_FastDFT2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) main_check_FastDFT.c $^ -o $(OUTPUT)

main_test_FastDFT: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_test_FastDFT2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) main_test_FastDFT.c $^ -o $(OUTPUT)	

main_check_FastSINE: $(BASIC_SOURCE) $(FT2) $(MATMUL)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_test_FastSINE: $(BASIC_SOURCE) $(FT2) $(MATMUL)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_find_gravitational_potential_with_fastsine: $(BASIC_SOURCE) $(FT2) $(MATMUL) $(FASTSINE2)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_mastery: $(BASIC_SOURCE) $(FT2) $(MATMUL) $(FASTSINE3) $(CUBE)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)






.PHONY:

clean:
	rm *.out && rm -rf $(OUTPUT).dSYM
