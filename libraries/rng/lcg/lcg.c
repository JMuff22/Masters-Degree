
double lcg(long long int *seed)
{
  static long long int a=69069,c=1,m=4294967296; /* 2^32 */
  static double rm=4294967296.0;

  *seed=(*seed * a+c)%m;
  return (double)*seed/rm;
}
