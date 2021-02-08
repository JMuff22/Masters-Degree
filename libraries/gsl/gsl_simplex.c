#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_vector.h>

/* Paraboloid centered on (dp[0],dp[1]) */

double my_f(const gsl_vector *v, void *params)
{
  double x, y;
  double *dp = (double *)params;
  
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  
  return 10.0 * (x - dp[0]) * (x - dp[0]) +
    20.0 * (y - dp[1]) * (y - dp[1]) + 30.0;
}

/* The gradient of f, df = (df/dx, df/dy). */
void my_df (const gsl_vector *v, void *params, gsl_vector *df)
{
  double x, y;
  double *dp = (double *)params;
  
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  
  gsl_vector_set(df, 0, 20.0 * (x - dp[0]));
  gsl_vector_set(df, 1, 40.0 * (y - dp[1]));
}

/* Compute both f and df together. */
void my_fdf (const gsl_vector *x, void *params, double *f, gsl_vector *df)
{
  *f = my_f(x, params);
  my_df(x, params, df);
}


int main(void)
{
  size_t np = 2;
  double par[2] = {1.0, 2.0};
     
  const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex;
  gsl_multimin_fminimizer *s = NULL;
  gsl_vector *ss, *x;
  gsl_multimin_function minex_func;
     
  size_t iter = 0, i;
  int status;
  double size;
     
  /* Initial vertex size vector */
  ss = gsl_vector_alloc (np);
     
  /* Set all step sizes to 1 */
  gsl_vector_set_all (ss, 1.0);
     
  /* Starting point */
  x = gsl_vector_alloc (np);
     
  gsl_vector_set (x, 0, 5.0);
  gsl_vector_set (x, 1, 7.0);
     
  /* Initialize method and iterate */
  minex_func.f = &my_f;
  minex_func.n = np;
  minex_func.params = (void *)&par;
     
  s = gsl_multimin_fminimizer_alloc (T, np);
  gsl_multimin_fminimizer_set (s, &minex_func, x, ss);
     
  do {
    iter++;
    status = gsl_multimin_fminimizer_iterate(s);
    if (status) break;
    size = gsl_multimin_fminimizer_size (s);
    status = gsl_multimin_test_size (size, 1e-4);
    printf("move ");
    for (i = 0; i < np; i++) printf ("%10.3e ", gsl_vector_get (s->x, i));
    printf("\n");
    //printf("func: %g\n",s->f);
  }
  while (status == GSL_CONTINUE && iter < 100);
  
  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);
  
  return status;
}

