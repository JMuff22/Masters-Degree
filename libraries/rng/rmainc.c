#include <stdio.h>
#include <stdlib.h>

double myrand(int *seed);

int main (int argc, char **argv)
{
  int seed,n,nmax;
  double r1,r2;

  seed=atoi(*++argv);
  nmax=atoi(*++argv);

  for (n=0;n<nmax;n++) {
    r1=myrand(&seed);
    r2=myrand(&seed);
    fprintf(stdout,"%15.12f %15.12g\n",r1,r2);
  }

}
