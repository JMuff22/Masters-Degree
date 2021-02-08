/*
 *
 *  iter.c	Number of iterations in Euclid's Alg.
 *
 *  Author:	Otmar Lendl (lendl@cosy.sbg.ac.at)
 *
 *  Copyright:	(c) 1994 by Otmar Lendl
 *		Send mail to ask about usage terms.
 *
 *  Last Modification: Fri Jan  5 18:49:29 MET 1996
 *
 */

#include "prng.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

struct rusage ru;
double user_time,new_user_time;

extern int iterations[];

int main()
{
s_prng_num i,a,p,i1,step;
prng_init_euclid_table();


printf("(* EUCLID_TABLE_SIZE = %d *)\n",EUCLID_TABLE_SIZE);
for(i=0;i<40;iterations[i++] = 0);

p = 2147483647;
step = 1000;

getrusage(RUSAGE_SELF,&ru);
user_time = ru.ru_utime.tv_sec + (0.000001 * ru.ru_utime.tv_usec);

for(a=p-1;a>0;a-=step)
	i1 = prng_inverse(a,p); 

getrusage(RUSAGE_SELF,&ru);
new_user_time = ru.ru_utime.tv_sec + (0.000001 * ru.ru_utime.tv_usec);


for(i=0;i<40;i++)
	printf("%ld\t%d\n",i,iterations[i]); 

printf("(* prng_inverse:\t%f secs user-time *)\n",new_user_time - user_time); 
fflush(stdout);

exit (0);
}
