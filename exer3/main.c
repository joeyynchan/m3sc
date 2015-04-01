#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/* Function Declaration */
void printInfo();
complex double* MakeWpowers(int N);


/* Function Implementation */
int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  printInfo();
  complex double* result = MakeWpowers(5);
  int i;
  for (i = 0; i < 5; i++)
  	printf("%10.6f %10.6f\n", creal(result[i]), cimag(result[i]));
  free(result);
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