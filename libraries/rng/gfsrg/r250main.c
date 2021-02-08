
#include <stdio.h>

int getseed();
double ran_number(int *seed);

int main(int argc, char **argv)
{
  int seed;
  int i,imax;
  double x,y;

  imax=atoi(*++argv);
  seed=atoi(*++argv);
  if (seed<=0) seed=getseed();
  fprintf(stderr,"Seed %d\n",seed);

  for(i=0; i<imax; i++) {
    x=ran_number(&seed); y=ran_number(&seed);
    fprintf(stdout,"%g %g\n",x,y);
  }
  return(0);
}


