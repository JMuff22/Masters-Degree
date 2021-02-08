#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int getseed();

int main (int argc, char **argv)
{
  double x,y,s=1.0;
  gsl_rng *r;
  int i,n,alg;
  unsigned long int seed;
  const gsl_rng_type *T;

  n=atoi(*++argv);
  seed=atoi(*++argv);
  alg=atoi(*++argv);
  
  if (seed<=0) seed=getseed();
  
  gsl_rng_env_setup();

  switch (alg) {
  case 0: T=gsl_rng_default; break;
  case 1: T=gsl_rng_mt19937; break;
  case 2: T=gsl_rng_ranlxs0; break;
  case 3: T=gsl_rng_ranlxs1; break;
  case 4: T=gsl_rng_ranlxs2; break;
  case 5: T=gsl_rng_ranlxd1; break;
  case 6: T=gsl_rng_ranlxd2; break;
  case 7: T=gsl_rng_ranlux; break;
  case 8: T=gsl_rng_ranlux389; break;
  case 9: T=gsl_rng_cmrg; break;
  case 10: T=gsl_rng_mrg; break;
  case 11: T=gsl_rng_taus; break;
  case 12: T=gsl_rng_taus2; break;
  case 13: T=gsl_rng_gfsr4; break;
  default: T=gsl_rng_default; break;
  }

  r = gsl_rng_alloc(T);
  gsl_rng_set(r,seed);
  fprintf(stderr,"Generator %s, seed %d\n",gsl_rng_name(r),seed);
  
  for (i = 0; i < n; i++) {
    x = gsl_ran_gaussian(r,s);
    y = gsl_ran_gaussian(r,s);
    printf ("%.8f %.8f\n",x,y);
  }
  
  gsl_rng_free (r);
  
  return 0;
}

