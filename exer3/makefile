GCC=gcc
SOURCE=MakeWpowers.c FastDFS.c FastDFT.c MatMul.c
SOURCEv2=MakeWpowers.c FastDFSv2.c FastDFTv2.c MatMul.c
FLAG=-ansi -pedantic -Wall -O3 -march=native -mfpmath=sse -funroll-loops

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

mainv2:
	$(GCC) $(FLAG) main.c $(SOURCEv2) -o main.out

.PHONY:

clean:
	rm *.out
