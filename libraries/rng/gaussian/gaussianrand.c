
double uniformrand(seed)
int *seed;

  /* ----------------------------------------------------------- */
  /* Park-Miller "minimal" Random number generator */
  /* uniform distribution ]0,1[ . See Numerical Recipes ch. 7.0 */
  /* ----------------------------------------------------------- */
{
  int IA,IM,IQ,IR,MASK;
  double AM,ans;
  int  k;

  IA=16807; IM=2147483647; AM=1.0/IM; IQ=127773; IR=2836; MASK=123459876;

  *seed= (*seed)^MASK;
  k=(*seed)/IQ;
  *seed = IA*((*seed)-k*IQ)-IR*k;
  if (*seed < 0) *seed = *seed+IM;
  ans=AM*(*seed);
  *seed= (*seed)^MASK;

  return(ans);
}



double gaussianrand(seed)
int  *seed;

  /* --------------------------------------------------------- */
  /* Random numbers with normal (Gaussian) distribution. */
  /* Mean is 0 and standard deviation is 1 */
  /* See W.H.Press et al., Numerical Recipes 1st ed., page 203 */
  /* --------------------------------------------------------- */
{
  double fac,v1,v2,r,ans;
  static double gset;
  static int iset=0;
  double uniformrand();

  if (iset==0) {
    do {
      v1 = 2.0*uniformrand(seed)-1.0;
      v2 = 2.0*uniformrand(seed)-1.0;
      r = v1*v1+v2*v2;
    } while (r>=1.0||r==0.0);
    fac = sqrt(-2.0*log(r)/r);
    gset = v1*fac;
    iset = 1;
    return(v2*fac);
  }
  else {
    iset = 0;
    return(gset);
  }
}
