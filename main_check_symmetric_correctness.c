#include <stdio.h>
#include <stdlib.h>

int main()
{

  int m = 0;
  int should_stop = 0;
  while(!should_stop)
  {
    int i;
    for (i = 4; i <= 6; i++)
    {
      int N = i*(int)pow(2, 3+m);
      double** M = MakeSN(N);
      double** MM = mymatmul(M, M, N-1, N-1, N-1);
      
    }
  }

}