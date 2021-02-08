#include <stdio.h>
#include <stdlib.h>

int getseed();
double lfg(long int *iseed);

int main (int argc, char **argv)
{
  long int seed;
  int i,imax;
  double x,y;

  imax=atoi(*++argv);
  seed=atoi(*++argv);
  if (seed<=0) seed=getseed(); 
  fprintf(stderr,"Seed %d\n",seed);

  for (i=0;i<imax;i++) {
    x=lfg(&seed);
    y=lfg(&seed);
    if (x<1e-4) fprintf(stdout,"%20.15g %20.15g\n",x,y);
  }

  return(0);
}
