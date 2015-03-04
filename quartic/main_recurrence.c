#include <stdio.h>
#include <math.h>

void printInfo();

int main()
{
	int argv[3];
	long double A, B, c;
	long double x[26];
	int i;

	printInfo();
	printf("Please enter the 3 parameters, I1, I2, I3 seperated with space:\n");
	scanf("%d %d %d", &argv[0], &argv[1], &argv[2]);

	A = argv[0]+1;
	B = -argv[0];
	c = (long double) argv[1]/ (long double)argv[2];
	x[0] = x[1] = c;
	for (i = 2; i < 26; i++)
	{
		x[i] = A*x[i-1] + B*x[i-2];
	}
	printf("x[2]-x[25] = %10.6Lg\n", x[2] - x[25]);
	return 0;
}



void printInfo()
{
  /* Chan, Joey, JMCSC, ync12 */
  
  /*printf("\n What is this? : \234 ");*/
  printf("\n");
  printf("%15s: %s\n", "Name", "Joey");
  printf("%15s: %s\n", "CID", "00730306");
  printf("%15s: %s\n", "LIBRARY NO", "0246734100");
  printf("%15s: %s\n", "Email Address", "ync12@ic.ac.uk");
  printf("%15s: %s\n", "Course Code", "JMCSC");
  printf("%15s: %s, %s \n", "Compile Time", __TIME__, __DATE__);
  printf("-------------------------------------------------\n");
}
