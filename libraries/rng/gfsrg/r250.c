#define NR 1000
#define NR250 1250
#define NRp1 1001
#define NR250p1 1251

double lcgy(int *seed) {
  static int   a=16807, m=2147483647, q=127773, r=2836;
  double minv = (double) 1.0/m;
  *seed = a*(*seed % q)-r*(*seed / q);
  if (*seed < 0) *seed = *seed + m;
  return (double) *seed * minv;
}

void r250(int *x,double *r,int n)
{
  static int q=103,p=250;
  static double rmaxin=2147483648.0; /* 2**31 */
  int i,k;
  for (k=1;k<=n;k++) {
    x[k+p]=x[k+p-q]^x[k];
    r[k]=(double)x[k+p]/rmaxin;
  }
  for (i=1;i<=p;i++) x[i]=x[n+i];
}

double ran_number(int *seed)
{
  double ret;
  static int firsttime=1;
  static int i,j=NR;
  static int x[NR250p1];
  static double r[NRp1];
  if (j>=NR) {
    if (firsttime==1) {
      for (i=1;i<=250;i++) x[i]=2147483647.0*lcgy(seed);
      firsttime=0;
    }
    r250(x,r,NR);
    j=0;
  }
  j++;
  return r[j];
}



