GCC=gcc
FLAGS=-ansi -pedantic -wall
COMPILE_FLAG=-O3 -march=native -mfpmath=sse -funroll-loops
SOURCE=mymatmul.c
VALGRIND=valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

all: main

main_check_correctness: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_correctness.c $(SOURCE) $(COMPILE_FLAG) -o main_check_correctness -lm

main_check_correctness_memcheck: main_check_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_correctness.c $(SOURCE) $(COMPILE_FLAG) -o main_check_correctness -lm && $(VALGRIND) ./main_check_correctness

main_speed_test: main_speed_test.c $(SOURCE)
	$(GCC) $(FLAG) main_speed_test.c $(SOURCE) $(COMPILE_FLAG) -o main_speed_test -lm

main_speed_test_memcheck: main_speed_test.c $(SOURCE)
	$(GCC) $(FLAG) main_speed_test.c $(SOURCE) $(COMPILE_FLAG) -o main_speed_test -lm && $(VALGRIND) ./main_speed_test

main_check_symmetric_correctness: main_check_symmetric_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_symmetric_correctness.c $(SOURCE) $(COMPILE_FLAG) -o main_check_symmetric_correctness -lm

main_check_symmetric_correctness_memcheck: main_check_symmetric_correctness.c $(SOURCE)
	$(GCC) $(FLAG) main_check_symmetric_correctness.c $(SOURCE) $(COMPILE_FLAG) -o main_check_symmetric_correctness -lm && $(VALGRIND) ./main_check_symmetric_correctness

main_find_gravitational_potential: main_find_gravitational_potential.c $(SOURCE)
	$(GCC) $(FLAG) main_find_gravitational_potential.c $(SOURCE) $(COMPILE_FLAG) -o main_find_gravitational_potential -lm

main_mastery: main_mastery.c $(SOURCE)
	$(GCC) $(FLAG) main_mastery.c $(SOURCE) $(COMPILE_FLAG) -o main_mastery -lm

main_mastery_plot: main_mastery_plot.c $(SOURCE)
	$(GCC) $(FLAG) main_mastery_plot.c $(SOURCE) $(COMPILE_FLAG) -o main_mastery_plot -lm

main_find_gravitational_potential_plot: main_find_gravitational_potential_plot.c $(SOURCE)
	$(GCC) $(FLAG) main_find_gravitational_potential_plot.c $(SOURCE) $(COMPILE_FLAG) -o main_find_gravitational_potential_plot -lm

main_single_speed_test: main_single_speed_test.c $(SOURCE)
	$(GCC) $(FLAG) main_single_speed_test.c $(SOURCE) $(COMPILE_FLAG) -o main_single_speed_test -lm

.PHONY: clean

clean:
	rm *.exe *.obj *.c~
