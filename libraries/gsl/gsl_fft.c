#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
     
#define DR(z,i) ((z)[2*(i)])    /* Real part      */
#define DI(z,i) ((z)[2*(i)+1])  /* Imaginary part */

double gasdev(int *);
     
int main (int argc, char **argv)
{
  int i,np,np2;
  double per1,per2,std,*data,sr,si;
  int seed;
  
  if (argc!=6) {
    fprintf(stderr,"Usage: %s np per1 per2 std seed\n",argv[0]);
    return (1);
  }
  np=atoi(*++argv);
  per1=atof(*++argv);
  per2=atof(*++argv);
  std=atof(*++argv);
  seed=atol(*++argv);
  np2=2*np;

  data=(double *) malloc((size_t)((2*np)*sizeof(double)));

  for (i=0;i<np;i++) {
    DR(data,i)=cos(2.0*M_PI*(i-1)/per1)+
               cos(2.0*M_PI*(i-1)/per2)+
               std*gasdev(&seed);
    DI(data,i)=0.0;
  }
  
  for (i=0;i<np;i++) {
    printf ("ORIG: %d %e %e\n",i,DR(data,i),DI(data,i));
  }
  printf ("\n");
  
  gsl_fft_complex_radix2_forward(data,1,np);
  
  for (i=0;i<np;i++) {
    sr=DR(data,i)*DR(data,i)/np;
    si=DI(data,i)*DI(data,i)/np;
    printf ("FFT: %d %g \n",i,sr+si);
  }
  
  return 0;
}


#include <math.h>

double gasdev(int *idum)
{
  double ran1(int *idum);
  static int iset=0;
  static double gset;
  double fac,rsq,v1,v2;
  
  if  (iset == 0) {
    do {
      v1=2.0*ran1(idum)-1.0;
      v2=2.0*ran1(idum)-1.0;
      rsq=v1*v1+v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac=sqrt(-2.0*log(rsq)/rsq);
    gset=v1*fac;
    iset=1;
    return v2*fac;
  } else {
    iset=0;
    return gset;
  }
}


#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran1(int *idum)
{
  int j;
  int k;
  static int iy=0;
  static int iv[NTAB];
  double temp;
  
  if (*idum <= 0 || !iy) {
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    for (j=NTAB+7;j>=0;j--) {
      k=(*idum)/IQ;
      *idum=IA*(*idum-k*IQ)-IR*k;
      if (*idum < 0) *idum += IM;
      if (j < NTAB) iv[j] = *idum;
    }
    iy=iv[0];
  }
  k=(*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if (*idum < 0) *idum += IM;
  j=iy/NDIV;
  iy=iv[j];
  iv[j] = *idum;
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp;
}
