GCC=gcc
SOURCE=MakeWpowers.c FastDFS.c MatMul.c
FLAG=-O3 -march=native -mfpmath=sse -funroll-loops

all:

main:
	$(GCC) $(FLAG) main.c $(SOURCE) -o main.out

.PHONY:

clean:
	rm *.out
