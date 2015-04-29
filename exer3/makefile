GCC=gcc
BASIC_SOURCE=MakeWpowers.c FastSINE.c info.c FastDFS.c FastDFT.c
FT1=FastTransform.c
FT2=FastTransform_v2.c
FASTSINE2=FastSINEv2.c
FASTSINE3=FastSINEv3.c
MATMUL=Matmul.c
MATMULC=MatmulC.c
CUBE=Cube.c
OUTPUT=main.out
CFLAGS=-g -ansi -pedantic -Wall -O3 -march=native -mfpmath=sse -funroll-loops

all:

main: $(BASIC_SOURCE) $(FAST1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_display_fdft: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_compare_fdfs_and_traditional: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_count_operation: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_fdfs_speed: $(BASIC_SOURCE) $(FT1) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_compare_fdfs_and_traditional_v2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_compare_fdfs_and_traditional_v3: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_fdfs_speed_v2: $(BASIC_SOURCE) $(FT2) $(MATMULC)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_check_fastsine_correctness: $(BASIC_SOURCE) $(FT2) $(MATMUL)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_display_fastsine: $(BASIC_SOURCE) $(FT2) $(MATMUL)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_find_gravitational_potential_with_fastsine: $(BASIC_SOURCE) $(FAST2) $(MATMUL) $(FASTSINE2)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

main_mastery: $(BASIC_SOURCE) $(FAST2) $(MATMUL) $(FASTSINE3) $(CUBE)
	$(GCC) $(CFLAGS) $@.c $^ -o $(OUTPUT)

.PHONY:

clean:
	rm *.out && rm -rf $(OUTPUT).dSYM
