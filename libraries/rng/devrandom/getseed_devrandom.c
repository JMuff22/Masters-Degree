#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define MASK 2147483647

int getseed()
{
  int i,rdev,rnum,nb=sizeof(int),rs;
  struct timeval tp;

  rdev=open("/dev/urandom",O_RDONLY);

  if (rdev==-1) {
    if (gettimeofday(&tp,(struct timezone *)NULL)==0) {
      i=tp.tv_sec+tp.tv_usec;
      i=(i%1000000)|1;
      return i;
    } else {
      return -1;
    }
  } else {
    rs=read(rdev,&rnum,nb);
    if (rs>0) {
      return MASK&rnum;
    } else {
      return -1;
    }
  }

}


int main(int argc, char **argv) {
  int i,j,n;

  n=atoi(*++argv);

  for (j=0;j<n;j++) {
    i=getseed();
    printf("%6d %12d\n",j,i);
  }


  return(0);

}

