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
 *  pairs.c	Overlapping Pairs
 *
 *  Author:	Otmar Lendl (lendl@cosy.sbg.ac.at)
 *
 *  Last Modification: Mon Jul 29 17:00:13 MET DST 1996
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prng.h"

struct prng_struct *generator;
char outfile[200] = "pairs.out";
FILE *out;

int main(int argc, char *argv[])
{
char input[100];
int i,npairs;
struct prng *g;

double x,y;

if (argc >= 2)
	g = prng_new(argv[1]);
else
	{
	printf("\nGenerator ? ");
	gets(input);
	g = prng_new(input);
	}

if( g==NULL )
	{
	printf("\nInitialisation of Generator failed ... exit\n\n");
	exit (-1);
	}


if (argc >= 3)
	npairs = atoi(argv[2]);
 else
 	{
	npairs = 10000;
	printf("\nHow many pairs [%d] ",npairs);
	gets(input);
	if (input[0] != 0 ) npairs = atoi(input);
	}

if (argc >= 4)
	(void) strncpy(outfile,argv[3],100);
else
	{
	printf("Output filename ('-' for stdout) ? [%s] ",outfile);
	gets(input);
	if (input[0] != 0 ) strncpy(outfile,input,100);
	}

out = (strcmp("-",outfile)) ? fopen(outfile,"w") : stdout ;

if (out == NULL)
        {
        perror("pairs: Cannot open log-file.\n");
        exit(1);
        }

fprintf(stderr,"%d pairs from %s\n",npairs,prng_long_name(g));

x =  prng_get_next(g);

for(i=0;i<npairs;i++)
{
y =  prng_get_next(g);
fprintf(out,"%.8f %.8f\n",x,y); 
x = y;
}
fclose(out);

prng_free(g);

return(0);
}
