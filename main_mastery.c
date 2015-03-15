#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

int main()
{
    int N = 3;
	double*** m = create_cube(N);
	int i, j, k, x= 1;
	for (i = 1; i <= N; i++)
	  for (j = 1; j <= N; j++)
	    for (k = 1; k <= N; k++)
	      m[i][j][k] = x++;
	print_cube(m, N);
	free_cube(m, N);
	return 0;
}