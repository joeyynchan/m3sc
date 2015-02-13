SOURCE=info.c rcubic_roots.c quad_roots.c lin_root.c
FLAG=-lm
GCC=gcc

all: main main_plot main_time test

main: main.c $(SOURCE)
	$(GCC) main.c $(SOURCE) -o $main.out $(FLAG)

test: test.c $(SOURCE)
	$(GCC) test.c $(SOURCE) -o test.out $(FLAG) && ./test.out

main_plot: main_plot.c $(SOURCE)
	$(GCC) main_plot.c $(SOURCE) -o main_plot.out

main_time: main_time.c
	$(GCC) main_time.c -o main_time.out

.PHONY: clean

clean:
	rm *.out *.c~
