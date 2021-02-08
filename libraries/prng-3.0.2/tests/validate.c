/*
 * Copyright (c) 1995 Otmar Lendl (lendl@cosy.sbg.ac.at)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted without a fee provided that the following
 * conditions are met:
 *
 * 1. This software is only used for private, research, or academic 
 *    purposes.
 *    
 * 2. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 3. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 4. Any changes made to this package must be submitted to the author.
 *    The legal status of the submitted changes must allow their inclusion
 *    into this package under this license.
 *
 * 5. Publications in the field of pseudorandom number generation, which
 *    made use of this package must include a reference to this package.
 *      
 * Any use of this software in a commercial environment requires a
 * written licence from the author. Contact Otmar Lendl 
 * (lendl@cosy.sbg.ac.at) to negotiate the terms.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * IN NO EVENT SHALL OTMAR LENDL BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES 
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR
 * NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 *
 */
/*
 *
 *  validate.c	Validation suite for the prng package
 *
 *  Author:	Otmar Lendl (lendl@cosy.sbg.ac.at)
 *
 *  Last Modification: Fri Aug  9 17:39:34 MET DST 1996
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "prng.h"


#define FABS(x) (x > 0) ? x : -(x)


struct prng_struct *generator;

void test_overflow()
{
prng_num u1,u2;
s_prng_num s1,s2;
int ok = TRUE;

printf("Testing additive overflow ...");

u2 = ~0UL;
u1 = u2 >> 1;	/* largest possible positive signed number */

s2 = u1;
s1 = u1 + 200;

if (s1 > 0 )
	ok = FALSE;

s1 -= 200;

if ((prng_num) s1 != u1)
	ok = FALSE;

puts( (ok) ? "\t... ok." : "\t... NOT ok.");
}



void test_mult_mod()
/*
 * things to test:
 *
 *	* power of 2 moduli
 *	* PRNG_SAVE_MAX bound
 *	* long long ints
 *
 */
{
prng_num u1,u2,m,a,s,res1,res2;
struct mult_mod_struct mm;
int ok;

printf("Testing modular multiplication ...\n");

u2 = ~0;
u1 = (u2 )>>1;	/* largest possible positive signed number */

m = u1 + 1;	/* highest power or 2 modulus possible */
ok = TRUE;
printf("\t power of 2 modulus ...");
for(a=1; a < m; a+= (m/127))
	{
	mult_mod_setup(a,m,&mm);

	for(s=0; s < m; s+= (m/17))
		{
		res1 = mult_mod(s,&mm);		/* what's usually used */

		res2 = mult_mod_generic(a,s,m);	/* most general alg. */

		if ( res1 != res2 )
			ok = FALSE;
		}

	}
puts( (ok) ? "\t... ok." : "\t... NOT ok.");

printf("\t small modulus ...");

m = 2 * PRNG_SAFE_MAX - 1;
ok = TRUE;
for(a=1; a < m; a+= (m/127))
	{
	mult_mod_setup(a,m,&mm);

	for(s=0; s < m; s+= (m/17))
		{
		res1 = mult_mod(s,&mm);		/* what's usually used */

		res2 = mult_mod_generic(a,s,m);	/* most general alg. */

		if ( res1 != res2 )
			ok = FALSE;
		}

	}

puts( (ok) ? "\t... ok." : "\t... NOT ok.");

printf("\t large modulus ...");
m = 7 * PRNG_SAFE_MAX - 1;
ok = TRUE;
for(a=1; a < m; a+= (m/127))
	{
	mult_mod_setup(a,m,&mm);

	for(s=0; s < m; s+= (m/17))
		{
		res1 = mult_mod(s,&mm);		/* what's usually used */

		res2 = mult_mod_generic(a,s,m);	/* most general alg. */

		if ( res1 != res2 )
			ok = FALSE;
		}

	}
puts( (ok) ? "\t... ok." : "\t... NOT ok.");

}


void test_samples(char *filename)
{
struct prng *g,*g2;
FILE *f;
char def[200],line[200];
double xf,xg,diff;
double samples[1024];
int ok,i,j,nrsamples;

if ( (f=fopen(filename,"r")) == NULL)
	{
	perror("Opening file with testcases");
	return;
	}

printf("Reading testcases from file %s\n",filename);
printf("On 32-bit computers tests with moduli larger than %d will fail.\n",INT_MAX);

while(!feof(f))
	{
	fgets(def,190,f);
	def[strlen(def)-1] = 0;	/* remove \n */
	printf("\t%s",def);
	g = prng_new(def);
	ok = (g) ? TRUE : FALSE;
	nrsamples = 0;

	while( (fgets(line,190,f) != NULL) && (strlen(line)>1))
		{
		xf = atof(line);
		samples[nrsamples++] = xf;
		xg = (g) ? prng_get_next(g) : -1.;
		diff = FABS(xf - xg);

		if( diff > 0.0000001 && ok)
			{
			ok = FALSE;
			line[strlen(line)-1] = 0;
			printf("\n%.15f (%s vs %.15f)",diff,line,xg);
			}
		}

/* reset and retest */

	if (g)
		{
		prng_reset(g);
		for(i=0;i<nrsamples;i++)
			{
			if (i == 5)	/* intersperse a run with a second generator */
				{
				g2 = prng_new(def);
				for(j=0;j<nrsamples;j++)
					{
					xg = prng_get_next(g2);
					diff = FABS(samples[j] - xg);
					if( diff > 0.0000001)
						{
						ok = FALSE;
						printf("\n%.15f (%.15f vs %.15f)",
								diff,samples[i],xg);
						}
					}
				prng_free(g2);
				}
			xg = prng_get_next(g);
			diff = FABS(samples[i] - xg);
			if( diff > 0.0000001)
				{
				ok = FALSE;
				printf("\n%.15f (%.15f vs %.15f)",diff,samples[i],xg);
				}
			}
		}

	puts( (ok) ? "\t... ok." : "\t... NOT ok.");
	}

fclose(f);
}

int do_alloc = TRUE;

void handler(int sig)
{
do_alloc = FALSE;
}


void test_alloc(char *gen)
{
struct prng *g;
int i;
double x;

printf("Testing memory management (hit ^c to move to next test)...\n");

signal(SIGINT,handler);
while(do_alloc)
	{
	g = prng_new(gen);
	if(g==NULL) continue;

	for(i=0;i<100;i++)
		x = prng_get_next(g);

	prng_free(g);
	}
}


int main(int argc, char *argv[])
{

test_overflow();
test_mult_mod();

/*
if(argc == 1)
	test_alloc("c(fish,eicg1,tt800)");
 else
	test_alloc(argv[1]);
*/

test_samples("tests.dat");

return(0);
}
