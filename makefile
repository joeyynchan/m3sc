GCC=gcc
FLAGS=-ansi -pedantic -wall
SOURCE=mymatmul.c
VALGRIND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

all: main

main_check_correctness: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_correctness.c $(SOURCE) -Ofast -o ./main_check_correctness -lm

main_check_correctness_memcheck: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main.c $(SOURCE) -o main_check_correctness -lm && $(VALGRIND) ./main_check_correctness

.PHONY: clean

clean:
	rm main.out
