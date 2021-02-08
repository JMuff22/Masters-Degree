#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv)
{
  int s1,a1,c1,s2,a2,c2,s0,s,a,c;
  int m=10000;
  int rd[m],r;
  int n,nmax,i,nnz,p;
  FILE *fd;

  s1=atoi(*++argv);
  s2=atoi(*++argv);
  a1=atoi(*++argv);
  a2=atoi(*++argv);
  c1=atoi(*++argv);
  c2=atoi(*++argv);
  nmax=atoi(*++argv);

  fd=fopen("nnz.dat","w");

  for (s0=s1;s<=s2;s++) {
    for (a=a1;a<=a2;a++) {
      for (c=c1;c<=c2;c++) {
	printf("%5d %5d %5d  ",s0,a,c);
	for (i=0;i<m;i++) rd[i]=0;
	s=s0;
	p=-1;
	for (n=0;n<nmax;n++) {
	  s=(s*a+c)%m;
	  rd[s]++;
	  if (s==s0 && p<0) p=n;
	}
	nnz=0;
	for (i=0;i<m;i++) if (rd[i]>0) nnz++;
	printf("       %5d %5d\n",nnz,p);
	fprintf(fd,"%6d ",nnz);
      }
      fprintf(fd,"\n");
    }
  }
  fclose(fd);
  
}
