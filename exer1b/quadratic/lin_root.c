int lin_root(double a1, double a0, double* r)
{
  /* No roots or every number is a root */
  if (a1 == 0)
    return a0 == 0 ? 0 : -1 ;
  /* Else find the root */
  *r = a0 == 0 ? 0 : -a0/a1;
  return 1;
}

