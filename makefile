all: Q1 Q2

Q1: exer_1a_1.c
	gcc exer_1a_1.c -o q1

Q2: exer_1a_2.c
	gcc exer_1a_2.c -o q2

clean:
	rm *.out
