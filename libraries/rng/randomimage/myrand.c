double myrand(long long int *seed) {

  static long long int a=69069,c=1,m=4294967296; /* 2^32 */
  static double rm=4294967296.0;

  *seed=(*seed * a+c)%m;
  return (double)*seed/rm;
}


double bmyrand(long long int *seed) {

  static int   a=16807, m=2147483647, q=127773, r=2836;  
  double minv = (double) 1.0/m;  
  
  *seed = a*(*seed % q)-r*(*seed / q);  
  if (*seed < 0) *seed = *seed + m;  
  return (double) *seed * minv; 
}


double cmyrand(long long int *seed) {

  static long long int a=269,c=0,m=1048576;
  static double rm=1048576.0;

  *seed=(*seed * a+c)%m;
  return (double)*seed/rm;
}


double dmyrand(long long int *seed) {

  static long long int a=269,c=0,m=2048;
  static double rm=2048.0;

  *seed=(*seed * a+c)%m;
  return (double)*seed/rm;
}


double emyrand(long long int *seed) {

  static long long int a=128,c=0,m=509;
  static double rm=509.0;

  *seed=(*seed * a+c)%m;
  return (double)*seed/rm;
}

