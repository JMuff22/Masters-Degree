#include <stdlib.h>
#include <sys/time.h>
int getseed()
{
  int i;
  struct timeval tp;
  if (gettimeofday(&tp,(struct timezone *)NULL)==0) {
    i=tp.tv_sec+tp.tv_usec;
    i=(i%1000000)|1;
    return i;
  } else {
    return -1;
  }
}
