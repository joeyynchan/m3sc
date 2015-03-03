GCC=gcc
FLAGS=-ansi -pedantic -wall
SOURCE=mymatmul.c

all: main

main: main.c $(SOURCE)
	$(GCC) $(FLAG) main.c $(SOURCE) -o main.out -lm


.PHONY: clean

clean:
	rm main.out
