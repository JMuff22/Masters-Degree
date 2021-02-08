/*
 *
 *  tuples.c	Generate overlapping tuples
 *
 *  Author:	Otmar Lendl (lendl@cosy.sbg.ac.at)
 *
 *  Last Modification: Sat Aug  3 22:54:51 MET DST 1996
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prng.h"

#define BUFLEN 256

int main(int argc, char *argv[])
{
int i,j,N,skip,dim, head, tail;
struct prng *g;

double b[BUFLEN];

if ((argc < 3) || (argc > 5))
	{
	fprintf(stderr,"Usage: %s dim N generator [skip]\n",argv[0]);
	exit(1);
	}

dim = atoi(argv[1]);
if (dim >= BUFLEN)
	{
	fprintf(stderr,"Dimension too large.\n");
	exit(2);
	}

N = atoi(argv[2]);

g = prng_new(argv[3]);
if( g==NULL )
        {
        printf("\nInitialisation of Generator failed ... exit\n\n");
        exit (-1);
        }



skip = 0;

if (argc == 5)
	skip = atoi(argv[4]);


fprintf(stderr,"%d %d-tuples from %s\n",N,dim,prng_long_name(g));


for(i=0;i<skip;i++)			/* do the skip */
	prng_get_next(g);

head = tail = 0;

for(i=0;i<(dim-1);i++)
	b[head++] = prng_get_next(g);

head--;

for(i=0;i<N;i++)
{

++head; head %= BUFLEN;

b[head] = prng_get_next(g);

for(j=0;j<dim;j++)
	{
	printf("%.12f ",b[(tail+j)%BUFLEN]);
	}
printf("\n"); 

++tail; tail %= BUFLEN;
}

prng_free(g);
return(0);
}
