double myrand(int *seed) {

/*  --------------------------- */
/*  Random number generator     */
/*  uniform distribution [0,1[  */
/*  --------------------------- */

  static int   a=16807, m=2147483647, q=127773, r=2836;  
  double minv = (double) 1.0/m;  
  
  *seed = a*(*seed % q)-r*(*seed / q);  
  if (*seed < 0) *seed = *seed + m;  
  return (double) *seed * minv; 
}
