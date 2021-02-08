#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_vector.h>

struct func_params {int ifunc, neval;};

double func_f(const gsl_vector *v, void *p)
{
  double x,y,ff;
  struct func_params *params=(struct func_params *)p;
  x=gsl_vector_get(v,0);
  y=gsl_vector_get(v,1);  
  switch (params->ifunc) {
  case 1: ff=10.0*(x-1.0)*(x-1.0)+20.0*(y-2.0)*(y-2.0)+30.0; break;
  case 2: ff=1.0-exp(-x*x/4.0)*sin(y)*sin(y); break;
  default: ff=1.0;
  }
  params->neval++;
  return ff;
}

void func_df (const gsl_vector *v, void *p, gsl_vector *df)
{
  double x,y,dfx,dfy,t;
  struct func_params *params=(struct func_params *)p;
  x=gsl_vector_get(v,0);
  y=gsl_vector_get(v,1);
  switch (params->ifunc) {
  case 1: 
    dfx=20.0*(x-1.0);
    dfy=40.0*(y-2.0);
    break;
  case 2:
    t=exp(-x*x/4.0);
    dfx=0.5*x*t*sin(y)*sin(y);
    dfy=-2.0*t*cos(y)*sin(y);
    break;
  default:
    dfx=0.0;
    dfy=0.0;
    break;
  }
  gsl_vector_set(df,0,dfx);
  gsl_vector_set(df,1,dfy);
}

void func_fdf (const gsl_vector *x, void *p, double *f, gsl_vector *df)
{
  *f=func_f(x,p);
  func_df(x,p,df);
}


int main (int argc, char **argv)
{
  int iter,max_iter;
  int status,ialg;
  const gsl_multimin_fdfminimizer_type *T;
  gsl_multimin_fdfminimizer *s;
  const gsl_multimin_fminimizer_type *Ts = gsl_multimin_fminimizer_nmsimplex;
  gsl_multimin_fminimizer *ss;
  gsl_vector *x,*step;
  gsl_multimin_function_fdf func;
  gsl_multimin_function funcs;
  double tol,x0,y0,step_size,ff;
  struct func_params p;
     
  if (argc!=8) {
    fprintf(stderr,"Usage: %s tol x0 y0 step_size maxiter ifunc ialg\n",argv[0]);
    return (1);
  }
  tol=atof(*++argv);
  x0=atof(*++argv);
  y0=atof(*++argv);
  step_size=atof(*++argv);
  max_iter=atoi(*++argv);
  p.ifunc=atoi(*++argv);
  ialg=atoi(*++argv);
  printf("# cmdline %g %g %g %g %d %d %d\n",tol,x0,y0,step_size,max_iter,p.ifunc,ialg);
  switch (ialg) {
  case 1: T=gsl_multimin_fdfminimizer_conjugate_fr; break;
  case 2: T=gsl_multimin_fdfminimizer_conjugate_pr; break;
  case 3: T=gsl_multimin_fdfminimizer_vector_bfgs; break;
  case 4: T=gsl_multimin_fdfminimizer_steepest_descent; break;
  default: T=gsl_multimin_fdfminimizer_conjugate_fr; break;
  }

  x=gsl_vector_alloc(2);
  gsl_vector_set(x,0,x0);
  gsl_vector_set(x,1,y0);
  if (ialg==5) {
      step = gsl_vector_alloc (2);
      gsl_vector_set_all (step, step_size);
  }

  p.neval=0;
  if (ialg<5) {
    func.f = &func_f;
    func.df = &func_df;
    func.fdf = &func_fdf;
    func.n = 2;
    func.params = (void *)&p;
  } else {
    funcs.f = &func_f;
    funcs.n = 2;
    funcs.params = (void *)&p;
  }
     
     
  if (ialg<5) {
    s=gsl_multimin_fdfminimizer_alloc(T,(size_t)2);
    gsl_multimin_fdfminimizer_set(s,&func,x,step_size,tol);
  } else {
    ss = gsl_multimin_fminimizer_alloc (Ts, 2);
    gsl_multimin_fminimizer_set (ss, &funcs, x, step);
  }

  if (ialg<5) 
    printf("# using %s method\n",gsl_multimin_fdfminimizer_name(s));
  else
    printf("# using %s method\n",gsl_multimin_fminimizer_name(ss));
  printf("#     i           x                  y               f(x,y)\n");

  iter=0;
     
  do
    {
      iter++;
      if (ialg<5)
	status = gsl_multimin_fdfminimizer_iterate(s);
      else
	status = gsl_multimin_fminimizer_iterate(ss);
      if (status) {
	fprintf(stderr,"*** Error: %s\n",gsl_strerror(status));
	break;
      }
      if (ialg<5) 
	status = gsl_multimin_test_gradient(s->gradient,tol);     
      else {
	step_size = gsl_multimin_fminimizer_size (ss);
	status = gsl_multimin_test_size (step_size, tol);
      }
      if (status == GSL_SUCCESS) printf("# Minimum found at:\n");
      ff=func_f(x,(void *)&p);
      if (ialg<5) 
	printf("%8d %18.10e %18.10e %18.10e\n",iter,gsl_vector_get(s->x,0),gsl_vector_get(s->x,1),ff);
      else
	printf("%8d %18.10e %18.10e %18.10e\n",iter,gsl_vector_get(ss->x,0),gsl_vector_get(ss->x,1),ff);      
    }
  while (status==GSL_CONTINUE && iter<max_iter);
     
  printf("# neval %d\n",p.neval);

  return 0;
}
