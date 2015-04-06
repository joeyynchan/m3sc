#include <stdio.h>
#include <stdlib.h>

void printInfo();

int main()
{
  /* Chan, Joey, JMCSC, ync12 */
  int i;
  int x[4] = {2, 2, 0, 0};
  int N = 2;

  printInfo();
  printf(" log2(N)     F+cN       F*cN       F+rN       F*rN   \n");
  printf("--------- ---------- ---------- ---------- ----------\n");

  for (i = 1; i<=20; i++)
  {
  	printf("%9d %10d %10d %10d %10d\n", i, x[0], x[1], x[2], x[3]);
  	N *= 2;
  	x[0] = x[0] * 2 + N;
  	x[1] = x[1] * 2 + N;
  	x[2] = x[2] * 2;
  	x[3] = x[3] * 2;
  }
  return 0;

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
