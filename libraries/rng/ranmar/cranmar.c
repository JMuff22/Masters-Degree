/* cranmar.c */

/**************************************************************************
*  RANMAR random number generator and initialization routine.
*  Propsed by Marsaglia and Zaman in FSU-SCRI-87-50
*  Modified my F.James 1988 to generate a vector, and translated to C
*  by Gabor Csanyi 1992
*
*  The bug fixed and zero values excluded by Jarkko Heinonen 1997.
*
*  ************************************************************************
*  the routine is VERY FAST with a period of 2^144
***************************************************************************/

void cranmar(float *vec,int len);
void crmarin(int ijkl);

float u[98], c, cd, cm;
int i97, j97;

/**************************************************************************
*  the vector random number generator, supply a 32-bit floating point vector
*  vec with length len to be filled with numbers. 
*  the routine 'rmarin' MUST be called before.
***************************************************************************/
void
cranmar(vec, len)
float *vec;
int len;
{
  int i;
  float uni;
  float zuni; /* added by J.H. to exclude zero */

  for(i = 0; i < len; i++){
    uni = u[i97] - u[j97];
    if(uni < 0)
      uni += 1.0;
    u[i97] = uni;
    i97 -= 1;
    if(i97 == 0)
      i97 = 97;
    j97 -= 1;
    if(j97 == 0)
      j97 = 97;
    c -= cd;
    if(c < 0)
      c += cm;
    uni -= c;
    if(uni < 0)
      uni += 1;
    vec[i] = uni;

    /* exclusion of zero according to ranmar.f added by J.H. */
   if(uni==0.0)
      {
	/* Replace exact zeros by uniform distr. *2**-24 */
	zuni=u[2] / 16777216.0;
	if(zuni==0.0)
	  {
	    zuni=(1./ 16777216.0)*(1./ 16777216.0);	    
	  }
	vec[i] = zuni;
      }

  }
}


/*************************************************************************
*  initialization routine for ranmar, called with an int.
*  to reproduce the original numbers of the author, call it with
*  54211737. but any number gives a disjoint sequence.
**************************************************************************/

void
crmarin(ijkl)
int ijkl;
{
  int ij, kl, i, j, k, l, ii, jj, m;
  float s, t;

  ij = ijkl / 30082;
  kl = ijkl - 30082 * ij;
  i = (ij / 177) % 177 + 2;
  j = ij % 177 + 2;
  k = (kl / 169) % 178 + 1;
  /* l = kl % 169 + 1; This was the error corrected by J. H. */
  l = kl % 169;

  for(ii = 1; ii < 98; ii++)
    {
      s = 0.0;
      t = 0.5;
      for(jj = 1; jj < 25; jj++)
	{
	  m = (((i*j) % 179) * k) % 179;
	  i = j;
	  j = k;
	  k = m;
	  l = (53*l + 1) % 169;
	  if((l * m) % 64 >= 32)
	    {
	      s = s+t;
	    }
	  t *= 0.5;
	}
      u[ii] = s;
    } /* ii */
  c = 362436. / 16777216.0;
  cd = 7654321. / 16777216.0;
  cm = 16777213. / 16777216.0;
  i97 = 97;
  j97 = 33;
}

