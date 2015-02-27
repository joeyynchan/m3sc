#include <stdio.h>
#include <math.h>

void printInfo();

int main()
{
	int argv[3];
	double A, B, c;
	double x[26];
	int i;

	printf("Please enter the 3 parameters, I1, I2, I3 seperated with space:\n");
	scanf("%d %d %d", &argv[0], &argv[1], &argv[2]);

	A = argv[0]+1;
	B = -argv[0];
	c = (double) argv[1]/ (double)argv[2];
	x[0] = x[1] = c;
	printf("x[0] = %20.10f\nx[1] = %20.10f\n", x[0], x[1]);
	for (i = 2; i < 26; i++)
	{
		/*x[i] = A*x[i-1] + B*x[i-2];*/
		x[i] = c + 0. * pow(-B, i);
		printf("x[%d] = %20.10f\n", i, x[i]);
	}
	printf("x[0]-x[25] = %20.10f\n", x[0] - x[25]);

	return 0;
}

void printInfo()
{
  /* Chan, Joey, JMC */
  
  /*printf("\n What is this? : \234 ");*/
  printf("\n");
  printf("Chan, Joey | JMC | Cubic Solver\n");
  printf("Compilation Time : %s, %s \n", __TIME__, __DATE__);
  printf("-------------------------------\n");
}
