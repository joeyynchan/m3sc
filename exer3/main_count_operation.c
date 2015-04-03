#include <stdio.h>
#include <stdlib.h>

void printInfo();

int main()
{
  int i;
  int x[4] = {0, 0, 2, 4};
  int N = 2;

  printInfo();
  printf(" log2(N)     F+cN       F*cN       F+rN       F*rN   \n");
  printf("--------- ---------- ---------- ---------- ----------\n");

  for (i = 1; i<=20; i++)
  {
  	printf("%9d %10d %10d %10d %10d\n", i, x[0], x[1], x[2], x[3]);
  	N *= 2;
  	x[0] = x[0] * 2;
  	x[1] = x[1] * 2 + N - 4;
  	x[2] = x[2] * 2;
  	x[3] = x[3] * 2 + 4;
  }

void execute_traditional(int N)
{
  complex double** y  = create_matrix(N, 1);
  complex double** Cn = create_matrix(N, N);
  complex double** x;
  double theta = 2.*PI/N;
  
  int i, j;
  for (i = 1; i <= N; i++)
  	y[i][1] = i + 0*I;

  
  for (i = 1; i <= N; i++)
  	for (j = 1; j <= N; j++)
  	  Cn[i][j] = cos(theta*(i-1)*(j-1)) + I*sin(theta*(i-1)*(j-1));

  x = matmul(Cn, y, N, N, 1);

  printf("\nTraditional way (N = %d) :\n", N);
  printf("==================\n");
  for (i = 1; i <= N; i++)
  	printf("x[%d] = %12.6f + %12.6fi\n", i, creal(x[i][1]), cimag(x[i][1]));

  free_matrix(x);
  free_matrix(y);
  free_matrix(Cn);
}

}

void printInfo()
{
  /* Chan, Joey, JMCSC, ync12 */
  printf("\n");
  printf("%15s: %s\n", "Name", "Joey");
  printf("%15s: %s\n", "CID", "00730306");
  printf("%15s: %s\n", "LIBRARY NO", "0246734100");
  printf("%15s: %s\n", "Email Address", "ync12@ic.ac.uk");
  printf("%15s: %s\n", "Course Code", "JMCSC");
  printf("%15s: %s, %s \n", "Compile Time", __TIME__, __DATE__);
  printf("-------------------------------------------------\n");
}
