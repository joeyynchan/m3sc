int lin_root(double* args, double* root)
{
  /* Chan, Joey, JMCSC, ync12 */

  int ONE_ROOT  = 1;
  int INF_ROOTS = 0;
  int NO_ROOT   = -1;

  double a1 = args[0];
  double a0 = args[1];

  /* No roots or every number is a root */
  if (a1 == 0)
    return a0 == 0 ? INF_ROOTS : NO_ROOT ;
  /* Else find the root */
  *(root+1) = a0 == 0 ? 0 : -a0/a1;
  return ONE_ROOT;
}

