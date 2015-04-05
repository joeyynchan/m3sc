GCC=gcc
SOURCE=MakeWpowers.c FastDFS.c FastDFT.c MatMul.c FastSINE.c
SOURCEv2=MakeWpowers.c FastDFSv2.c FastDFTv2.c MatMul.c FastSINE.c
SOURCEv3=MakeWpowers.c FastDFSv2.c FastDFTv2.c FastSINE.c
FLAG=-g -ansi -pedantic -Wall -O3 -march=native -mfpmath=sse -funroll-loops

all:

main:
	$(GCC) $(FLAG) main.c $(SOURCE) -o main.out

main_display_fdft:
	$(GCC) $(FLAG) main_display_fdft.c $(SOURCE) -o main.out

main_compare_fdfs_and_traditional:
	$(GCC) $(FLAG) main_compare_fdfs_and_traditional.c $(SOURCE) -o main.out

main_count_operation:
	$(GCC) $(FLAG) main_count_operation.c $(SOURCE) -o main.out

main_fdfs_speed:
	$(GCC) $(FLAG) main_fdfs_speed.c $(SOURCE) -o main.out

main_compare_fdfs_and_traditional_v2:
	$(GCC) $(FLAG) main_compare_fdfs_and_traditional.c $(SOURCEv2) -o main.out

main_fdfs_speed_v2:
	$(GCC) $(FLAG) main_fdfs_speed.c $(SOURCEv2) -o main.out

main_check_fastsine_correctness:
	$(GCC) $(FLAG) main_check_fastsine_correctness.c $(SOURCEv3) -o main.out

main_display_fastsine:
	$(GCC) $(FLAG) main_display_fastsine.c $(SOURCEv3) -o main.out

.PHONY:

clean:
	rm *.out
