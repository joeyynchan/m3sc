SOURCE=rcubic_roots.c quad_roots.c lin_root.c
SOURCE_C=complex_rcubic_roots.c complex_quad_roots.c complex_lin_root.c
FLAG=-lm
GCC=gcc

all: main test

main: main.c $(SOURCE)
	$(GCC) main.c $(SOURCE) -o main.out $(FLAG)

test: test.c $(SOURCE)
	$(GCC) test.c $(SOURCE) -o test.out $(FLAG) && ./test.out


.PHONY: clean

clean:
	rm *.out *.c~
