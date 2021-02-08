#include <stdio.h>
#include <gsl/gsl_qrng.h>

int main (int argc, char **argv)
{
  int i,n;
  //gsl_qrng *q=gsl_qrng_alloc(gsl_qrng_sobol,2);
  gsl_qrng *q=gsl_qrng_alloc(gsl_qrng_niederreiter_2,2);
  
  n=atoi(*++argv);

  for (i=0;i<n;i++)
    {
      double v[2];
      gsl_qrng_get(q,v);
      printf("%.5f %.5f\n",v[0],v[1]);
    }
  
  gsl_qrng_free(q);
  return 0;
}
