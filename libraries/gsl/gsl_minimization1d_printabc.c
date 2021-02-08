#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>

#define ABS(x) sqrt((x)*(x))

     
struct func_params {int ifunc;};

double func(double x, void * p) {
  struct func_params *params=(struct func_params *)p;
  double ff;
  switch (params->ifunc) {
  case 1: ff=j0(x); break;
  case 2: ff=sin(-x)*exp(-x*x); break;
  case 3: ff=sin(x); break;
  case 4: ff=cos(x) + 1.0; break;
  default: ff=0.0; break;
  }
  //printf("f %g %g\n",x,ff);
  return ff;
}
     
double funcd(double x, void * p) {
  struct func_params *params=(struct func_params *)p;
  double ff;
  switch (params->ifunc) {
  case 1: ff=0; break;
  case 2: ff=2.0*x*exp(-x*x)*sin(x)-exp(-x*x)*cos(x); break;
  case 3: ff=cos(x); break;
  case 4: ff=-sin(x); break;
  default: ff=0.0; break;
  }
  //printf("d  %g %g\n",x,ff);
  return ff;
}

int main (int argc, char **argv)
{
  int status;
  int iter, max_iter, ialg;
  const gsl_min_fminimizer_type *T;
  gsl_min_fminimizer *s;
  double a,b,c,tol,f,df;
  gsl_function F;
  struct func_params p;
     
  if (argc!=8) {
    fprintf(stderr,"Usage: %s tol a b c maxiter ifunc ialg\n",argv[0]);
    return (1);
  }
  tol=atof(*++argv);
  a=atof(*++argv);
  b=atof(*++argv);
  c=atof(*++argv);
  max_iter=atoi(*++argv);
  p.ifunc=atoi(*++argv);
  ialg=atoi(*++argv);

  switch (ialg) {
  case 1: T=gsl_min_fminimizer_goldensection; break;
  case 2: T=gsl_min_fminimizer_brent; break;
  default: T=gsl_min_fminimizer_goldensection; break;
  }

  F.function = &func;
  F.params = &p;  
  s = gsl_min_fminimizer_alloc(T);
  gsl_min_fminimizer_set(s,&F,b,a,c);

  iter=0;

  printf ("%18g %18g %18g %18g %18g %18g\n",a,b,c,func(a,&p),func(b,&p),func(c,&p));

  do
    {
      iter++;
      status = gsl_min_fminimizer_iterate(s);
      b = gsl_min_fminimizer_x_minimum(s);
      a = gsl_min_fminimizer_x_lower(s);
      c = gsl_min_fminimizer_x_upper(s);
      status=gsl_min_test_interval(a,c,tol,0.0);
      if (status == GSL_SUCCESS) printf ("# Converged:\n");
      f=func(c,&p);
      df=funcd(c,&p);
      printf ("%18g %18g %18g %18g %18g %18g\n",a,b,c,func(a,&p),func(b,&p),func(c,&p));
    }
  while (status==GSL_CONTINUE && iter<max_iter);
  return status;
}
