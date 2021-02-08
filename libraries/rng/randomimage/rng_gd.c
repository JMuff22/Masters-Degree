/* 
   Generate a jpg image from output of a random number generator (RNG)
   (function myrand(&seed)). All three color components (RGB) are
   calculated from RNG output: evenly distributed double in [0,1).

   Uses the gd library and functions 
       myrand(&seed) : returns the random number, double
       getseed()     : returns an integer seed calculated based on time.

   Compilation: gcc rng_gd.c myrand.c getseed.c -lgd

             Antti Kuronen, 2006, 2009
             antti.kuronen@helsinki.fi

*/

#include "gd.h"
#include <stdio.h>
#include <stdlib.h>

double myrand(long long int *seed);
int getseed();

int main(int argc, char **argv) {

  gdImagePtr im;
  FILE *jpegout;
  long long int seed;
  int x,y,i,j,r,g,b,color;
  char *fn;
  int dist[512];

  if (argc!=5) {
    fprintf(stderr,"Usage: %s jpgfile seed width height\n",argv[0]);
    return(1);
  }

  fn=*++argv;  
  seed=atoi(*++argv);  
  x=atoi(*++argv);
  y=atoi(*++argv);
  if (seed<1) {
    seed=getseed();
    fprintf(stderr,"Seed from time: %d\n",seed);
  }

  im = gdImageCreateTrueColor(x,y);

  for (i=0;i<512;i++) dist[i]=0;

  for (i=0;i<x;i++) {
    for (j=0;j<y;j++) {
      r=(int)(256.0*myrand(&seed));
      g=(int)(256.0*myrand(&seed));
      b=(int)(256.0*myrand(&seed));      
      dist[r]++;dist[g]++;dist[b]++;
      color=gdImageColorAllocate(im,r,g,b);
      gdImageSetPixel(im,i,j,color);
    }
  }

  jpegout = fopen(fn, "wb");
  gdImageJpeg(im, jpegout, -1);
  fclose(jpegout);

  for (i=0;i<512;i++) fprintf(stdout,"%d %d\n",i,dist[i]);

  gdImageDestroy(im);

}

