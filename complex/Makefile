SOURCE=rquartic_roots.c rcubic_roots.c quad_roots.c lin_root.c
SOURCE_C=complex_rcubic_roots.c complex_quad_roots.c complex_lin_root.c
GCC=gcc -ansi -pedantic -Wall

all: main test

main_c89: main.c $(SOURCE)
	$(GCC) main.c $(SOURCE) -o main.out -lm

main:  main.c $(SOURCE)
	gcc main.c $(SOURCE) -o main.out -lm

test: test.c $(SOURCE)
	$(GCC) test.c $(SOURCE) -o test.out -lm


.PHONY: clean

clean:
	rm *.out *.c~
