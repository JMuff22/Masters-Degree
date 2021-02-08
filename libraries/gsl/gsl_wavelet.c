#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_wavelet.h>
     
int main (int argc, char **argv)
{
  int i,j,n,nc,alg,K,zero;
  double *data,*abscoeff,mina;
  size_t *p;
  gsl_wavelet *w;
  gsl_wavelet_workspace *work;
  FILE *fd;
  const gsl_wavelet_type *W[]={gsl_wavelet_daubechies, 
			       gsl_wavelet_daubechies_centered,
			       gsl_wavelet_haar,
			       gsl_wavelet_haar_centered,
			       gsl_wavelet_bspline,
			       gsl_wavelet_bspline_centered};

  if (argc!=6) {
    fprintf(stderr,"usage: %s n nc mina alg K\n",*argv);
    return(-1);
  }
  n=atoi(*++argv);
  nc=atoi(*++argv);
  mina=atof(*++argv);
  alg=atoi(*++argv);
  K=atoi(*++argv);
  
  data=malloc(n*sizeof (double));
  abscoeff=malloc(n*sizeof(double));
  p=malloc(n*sizeof(size_t));
  
  for (i=0;i<n;i++) scanf("%d %lg",&j,&data[i]);  
  
  if ((int*)(w=gsl_wavelet_alloc(W[alg],K)) == NULL) {
    fprintf(stderr,"Error in allocating wavelet\n");
    return(-1);
  }
  fprintf(stderr,"Wavelet = %s\n",gsl_wavelet_name(w));
  work=gsl_wavelet_workspace_alloc(n);

  gsl_wavelet_transform_forward(w,data,1,n,work);
  for (i=0;i<n;i++) abscoeff[i]=fabs(data[i]);
  gsl_sort_index(p,abscoeff,1,n);
  zero=0;
  for (i=0;i<n;i++) if (abscoeff[i]<mina || i<n-nc) {zero++;data[p[i]]=0;}
  gsl_wavelet_transform_inverse(w,data,1,n,work);
  fprintf(stderr,"Zero = %d\n",zero);
  
  for (i=0;i<n;i++) printf("%d %g\n",i,data[i]);

  fd=fopen("abscoeffs.out","w");
  fprintf(fd,"# ");
  for (i=0;i<n;i++) fprintf(fd,"%d %g\n",i,abscoeff[i]);
  fclose(fd);
}

