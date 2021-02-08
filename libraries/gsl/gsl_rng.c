#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>

int getseed();

int main (int argc, char **argv)
{
  double x,y,xmax;
  gsl_rng *r;
  int i,n,alg;
  unsigned long int seed;
  const gsl_rng_type *T[]={
    gsl_rng_mt19937      , gsl_rng_ranlxs0      , gsl_rng_ranlxs1      ,
    gsl_rng_ranlxs2      , gsl_rng_ranlxd1      , gsl_rng_ranlxd2      ,
    gsl_rng_ranlux       , gsl_rng_ranlux389    , gsl_rng_cmrg         ,
    gsl_rng_mrg          , gsl_rng_taus         , gsl_rng_taus2        ,
    gsl_rng_gfsr4        , gsl_rng_rand         , gsl_rng_random_bsd   ,
    gsl_rng_random_libc5 , gsl_rng_random_glibc2, gsl_rng_rand48       ,
    gsl_rng_ranf         , gsl_rng_ranmar       , gsl_rng_r250         ,
    gsl_rng_tt800        , gsl_rng_vax          , gsl_rng_transputer   ,
    gsl_rng_randu        , gsl_rng_minstd       , gsl_rng_uni          ,
    gsl_rng_uni32        , gsl_rng_slatec       , gsl_rng_zuf          ,
    gsl_rng_borosh13     , gsl_rng_coveyou      , gsl_rng_fishman18    ,
    gsl_rng_fishman20    , gsl_rng_fishman2x    , gsl_rng_knuthran2    ,
    gsl_rng_knuthran     , gsl_rng_lecuyer21    , gsl_rng_waterman14   };

  
  if (argc!=5) {
    fprintf(stderr,"usage: n seed alg xmax\n");
    return 0;
  }
  n=atoi(*++argv);
  seed=atoi(*++argv);
  alg=atoi(*++argv);
  xmax=atof(*++argv);
  
  if (seed<=0) seed=getseed();
  
  gsl_rng_env_setup();

  r = gsl_rng_alloc(T[alg]);
  gsl_rng_set(r,seed);
  fprintf(stderr,"Generator %s, seed %d  ",gsl_rng_name(r),seed);
  
  for (i = 0; i < n; i++) {
    x = gsl_rng_uniform (r);
    y = gsl_rng_uniform (r);
    if (x<xmax) printf ("%.8f %.8f\n",x,y);
  }
  
  gsl_rng_free (r);
  
  fprintf(stderr,"  CPU time %g sec\n",
	  (double)clock()/(double)CLOCKS_PER_SEC);
  return 0;
}

