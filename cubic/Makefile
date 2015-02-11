SOURCE=main.c info.c rcubic_roots.c quad_roots.c lin_root.c
OUTPUT=main
FLAG=-lm
GCC=gcc

all: main

main: $(SOURCE)
	$(GCC) $(SOURCE) -o $(OUTPUT) $(FLAG)

clean:
	rm $(OUTPUT)
