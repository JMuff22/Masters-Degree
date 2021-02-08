#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main (int argc, char **argv)
{
  int i,nk,np;
  double *x,*y,x1,x2,dx,xi,yi;
  gsl_interp_accel *acc;  
  gsl_spline *spline;
  
  if (argc!=4) {
    fprintf(stderr,"Usage: %s x1 x2 dx\n",argv[0]); return (1);
  }
  x1=atof(*++argv);
  x2=atof(*++argv);
  dx=atof(*++argv);

  fscanf(stdin,"%d",&nk);
  x = (double *) malloc((size_t) (nk*sizeof(double)));  
  y = (double *) malloc((size_t) (nk*sizeof(double)));  
  for (i=0;i<nk;i++) fscanf(stdin,"%lg %lg",&x[i],&y[i]);
  
  acc = gsl_interp_accel_alloc();
  spline = gsl_spline_alloc(gsl_interp_cspline,nk);
  
  gsl_spline_init(spline,x,y,nk);
  
  np=(x2-x1)/dx;
  for (i=0;i<np;i++) {
    xi=x1+dx*i;
    yi=gsl_spline_eval(spline,xi,acc);
    printf("%g %g\n",xi,yi);
  }
  gsl_spline_free(spline);
  gsl_interp_accel_free(acc);

  return 0;
}
