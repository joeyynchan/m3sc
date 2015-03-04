GCC=gcc
FLAGS=-ansi -pedantic -wall
SOURCE=mymatmul.c
VALGRIND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

all: main

main: main.c $(SOURCE)
	$(GCC) $(FLAG) main.c $(SOURCE) -o main.out -lm

main_memcheck: main.c $(SOURCE)
	$(GCC) $(FLAG) main.c $(SOURCE) -o main.out -lm && $(VALGRIND) ./main.out 

.PHONY: clean

clean:
	rm main.out
