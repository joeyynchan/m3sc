#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int rquartic_roots(double*, double*);

int main()
{
  /* Chan, Joey, JMC */

  double X = 1./5.;
  double Y = 1./3.;
  double b;
  double argv[4];
  double roots[5];
  int real_root_count = 0;
  int result;
  int i;

  printf("  b       Re(t)       Im(t)         theta    \n");
  printf("----- ------------ ------------ -------------\n");
  for (b = 0.05; b <= 0.95; b+=0.05)
  {
  	argv[0] = (2*X + 2 - 2*b*b)/(b*Y);
  	argv[1] = 0;
  	argv[2] = (2*X - 2 + 2*b*b)/(b*Y);
  	argv[3] = -1.;

  	result = rquartic_roots(argv, roots);
  	switch (result)
  	{
  	  case 2:
  	  {
        real_root_count += 2;
  	  	printf("%5.2f %12.6f %12s %12.6f\n", b, roots[1], "", atan(roots[1])*2*180/PI);
  	  	printf("%5s %12.6f %12s %12.6f\n",  "", roots[2], "", atan(roots[2])*2*180/PI);
  	  	printf("%5s %12.6f %12.6f %12s\n",  "", roots[3], -roots[4], "");
  	  	printf("%5s %12.6f %12.6f %12s\n",  "", roots[3],  roots[4], "");
  	  	break;
  	  }
  	  case 0:
      {
        real_root_count += 0;
  	  	printf("%5.2f %12.6f %12.6f %12s\n", b, roots[1], -roots[2], "");
  	  	printf("%5s %12.6f %12.6f %12s\n",  "", roots[1],  roots[2], "");
  	  	printf("%5s %12.6f %12.6f %12s\n",  "", roots[3], -roots[4], "");
  	  	printf("%5s %12.6f %12.6f %12s\n",  "", roots[3],  roots[4], "");
  	  	break;
  	  }
  	  default:
  	  {
        real_root_count += 4;
  	  	printf("%5.2f %12.6f %12s %12.6f\n", b, roots[1], "", atan(roots[1])*2*180/PI);
  	  	printf("%5s %12.6f %12s %12.6f\n",  "", roots[2], "", atan(roots[2])*2*180/PI);
  	  	printf("%5s %12.6f %12s %12.6f\n",  "", roots[3], "", atan(roots[3])*2*180/PI);
  	  	printf("%5s %12.6f %12s %12.6f\n",  "", roots[4], "", atan(roots[4])*2*180/PI);
  	  	break;
  	  }
  	}
  }

  printf("\nThere are %d real values of t that satisfy the quartic polynomial.\n", real_root_count);

  b = 0.05;
  for (i = 0; i < 10; i++)
  {
    argv[0] = (2*X + 2 - 2*b*b)/(b*Y);
    argv[1] = 0;
    argv[2] = (2*X - 2 + 2*b*b)/(b*Y);
    argv[3] = -1.;
    result = rquartic_roots(argv, roots);
    while (result != 2 && result != 0)
    {
      b+= pow(10., -i);
      argv[0] = (2*X + 2 - 2*b*b)/(b*Y);
      argv[1] = 0;
      argv[2] = (2*X - 2 + 2*b*b)/(b*Y);
      argv[3] = -1.;
      result = rquartic_roots(argv, roots);
    }
    b-=pow(10., -i);
  }
  
  argv[0] = (2*X + 2 - 2*b*b)/(b*Y);
  argv[1] = 0;
  argv[2] = (2*X - 2 + 2*b*b)/(b*Y);
  argv[3] = -1.;
  result = rquartic_roots(argv, roots);

  printf("\nThe maximum value of b for which there are 4 real roots is %10.8g\n", b);

  return 0;
}
