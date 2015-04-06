#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

/* Function Declaration */
complex double** create_matrix(int row, int col);
void free_matrix(complex double** matrix);
complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2);



/* Function Implementation */
complex double** create_matrix(int row, int col)
{
  /* Chan, Joey, JMCSC, ync12 */
  int n;
  complex double** m = (complex double**) calloc(row+1, sizeof(complex double*));
  m[0] = (complex double*) calloc(row*col+1, sizeof(complex double));
  m[1] = m[0];
  for (n = 2; n <= row; n++)
    m[n] = m[n-1]+col;
  return m;
}

void free_matrix(complex double** matrix)
{
  /* Chan, Joey, JMCSC, ync12 */
  free(matrix[0]);
  free(matrix);
}

complex double **matmul(complex double** m1,
	                    complex double** m2,
	                    int row1,
	                    int col1,
	                    int col2)
{
  /* Chan, Joey, JMCSC, ync12 */
  int i, j, k;
  complex double** m = create_matrix(row1, col2);

  #pragma omp parallel for
  for (i = 1; i <= row1; i++)
  {
    complex double* m1_row_i = m1[i];
    complex double* m_row_i = m[i];
    for (k = 1; k <= col1; k++)
    {
      complex double* m2_row_k = m2[k];
      complex double m1_ik = m1_row_i[k];
      for (j = 1; j <= col2; j++)
        m_row_i[j] += m1_ik * m2_row_k[j];
    }
  }
  return m;
}
