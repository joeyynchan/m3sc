GCC=gcc
FLAGS=-ansi -pedantic -wall
SOURCE=mymatmul.c
VALGRIND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

all: main

main_check_correctness: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_correctness.c $(SOURCE) -Ofast -o main_check_correctness -lm

main_check_correctness_memcheck: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_correctness.c $(SOURCE) -Ofast -o main_check_correctness -lm && $(VALGRIND) ./main_check_correctness

main_speed_test: main_speed_test.c $(SOURCE)
	$(GCC) $(FLAG) main_speed_test.c $(SOURCE) -Ofast -o main_speed_test -lm

main_speed_test_memcheck: main_speed_test.c $(SOURCE)
	$(GCC) $(FLAG) main_speed_test.c $(SOURCE) -Ofast -o main_speed_test -lm && $(VALGRIND) ./main_speed_test

main_check_symmetric_correctness: main_check_symmetric_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_symmetric_correctness.c $(SOURCE) -Ofast -o main_check_symmetric_correctness -lm

main_check_symmetric_correctness_memcheck: main_check_symmetric_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_symmetric_correctness.c $(SOURCE) -Ofast -o main_check_symmetric_correctness -lm && $(VALGRIND) ./main_check_symmetric_correctness

main_find_gravitational_potential: main_find_gravitational_potential.c $(SOURCE)
	$(GCC) $(FLAG) main_find_gravitational_potential.c $(SOURCE) -Ofast -o main_find_gravitational_potential -lm

.PHONY: clean

clean:
	rm main_check_correctness main_speed_test
