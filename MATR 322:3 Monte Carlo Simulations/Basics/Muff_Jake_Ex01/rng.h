#include <stdlib.h>

unsigned long int lcg_s = 1; // lcg seed
unsigned long int pm_s= 1; // pm seed

/* Lines for the Mersenne twister directly copied from http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/MT2002/emt19937ar.html mt19937ar.c    */
/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */


void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
double genrand_real3(void);




double rand_lcg();
double rand_lcg_interval();


double rand_pm();
double rand_pm_interval();

void seed_lcg(int seed);
void seed_pm(int x);

void seed_lcg(int seed){

    lcg_s = seed;
}

void seed_pm(int seed){

    pm_s = seed;
}

double rand_lcg(){
    double x;
    int a, c, m;
    m = 113829760;
    c=7371;
    a=3557181;
    x = (a * lcg_s + c) % m;
    lcg_s = x;
    return x/m;
}

double rand_lcg_interval(){
    double x=0.0;
    int a, c, m;
    int interval_count=0;
    m = 113829760;
    c=7371;
    a=3557181;
    double x_new=lcg_s;
    while (x != x_new){
        x = (a * lcg_s + c) % m;
        //std::cout << x << std::endl;

        lcg_s = x;
        interval_count+=1;

    }
    return interval_count;
}

double rand_pm(){ //with schrage algorithm. Taken from lecture notes **Num recipes**
    int a = 16807;
    int q = 127773;
    int r = 2836;
    int m = 2147483647;
    
    long k;
    double ans;
    k = pm_s / q;
    pm_s = a *(pm_s - k*q) - r*k;
    if(pm_s < 0){
        pm_s += m;
    }
    ans = (1.0/m) * (pm_s);





    return ans;
}

double rand_pm_interval(){ //with schrage algorithm 
    int a = 16807;
    int q = 127773;
    int r = 2836;
    int m = 2147483647;

    int interval_count=0;
    long x=0;
    double x_new = pm_s;
    while(x != x_new){
    long k = pm_s/q;
    long l = pm_s -q * k;
    x = a * l - r*k;
    if (x > 0){
        pm_s = x;
    }
    else{
        pm_s = x + m;
    }
    interval_count +=1;
    }



    return interval_count;
}

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

