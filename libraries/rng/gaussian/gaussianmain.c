#include <stdio.h>
#include <stdlib.h>

double gaussianrand(int *seed);

int main (int argc, char **argv)
{
  int seed=13579,n,nmax;

  for (n=0;n<10000;n++)
    fprintf(stdout,"%e %e\n",gaussianrand(&seed),gaussianrand(&seed));

}
