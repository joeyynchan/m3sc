int lin_root(double* a, double* r)
{
  /* Chan, Joey, JMC */
  double a1 = a[0];
  double a0 = a[1];

  /* No roots or every number is a root */
  if (a1 == 0)
    return a0 == 0 ? 0 : -1 ;
  /* Else find the root */
  *r = a0 == 0 ? 0 : -a0/a1;
  return 1;
}

