#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f (double x, void * params) {
  double alpha = *(double *) params;
  double f = alpha/(1.0+x*x);
  return f;
}

int main (void)
{
  gsl_integration_workspace *w; 
  double result, error;
  double expected = M_PI;
  double alpha = 4.0;
  gsl_function F;
  int key=GSL_INTEG_GAUSS15;

  w = gsl_integration_workspace_alloc(1000);
  F.function = &f;
  F.params = &alpha;
  
  gsl_integration_qag(&F,0.0,1.0,0,1e-10,1000,key,w,&result,&error); 
  
  printf("result          = % .18f\n", result);
  printf("exact result    = % .18f\n", expected);
  printf("estimated error = % .18f\n", error);
  printf("actual error    = % .18f\n", result - expected);
  printf("intervals =  %d\n", w->size);
  
  return 0;
}
