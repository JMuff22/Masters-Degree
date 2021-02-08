/* 
   Uses the gd library.
   Compilation: gcc rng_gd.c myrand.c getseed.c -lgd
*/

#include "gd.h"
#include <stdio.h>
#include <stdlib.h>

double myrand(long long int *seed);
int getseed();

int main(int argc, char **argv) {

  gdImagePtr im;
  FILE *pngout, *jpegout;
  long long int seed;
  int x,y,i,j,r,g,b,color;
  char *fn;
  int dist[512];

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
      r=g=b=(int)(256.0*myrand(&seed));
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

