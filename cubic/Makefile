SOURCE=info.c rcubic_roots.c quad_roots.c lin_root.c
OUTPUT=main
FLAG=-lm
GCC=gcc

all: main

main: main.c $(SOURCE)
	$(GCC) main.c $(SOURCE) -o $(OUTPUT) $(FLAG)

test: test.c $(SOURCE)
	$(GCC) test.c $(SOURCE) -o test $(FLAG) && ./test

clean:
	rm test $(OUTPUT)
