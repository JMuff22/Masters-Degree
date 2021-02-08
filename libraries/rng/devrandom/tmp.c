#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) 

{

  int i,j,rdev; 
  int rand[100];  

  for(i=0;i<10;i++) {   

    rdev=open("/dev/urandom",O_RDONLY); 
    if (!rdev) {
      printf("open random device error\n"); 
      exit(-1);
    }

    for (i=0;i<100;i++) {   
      read(rdev,rand,10);
      for(j=0;j<2;j++)printf(" %d",rand[j]);    printf("\n"); 
    }
  }

  
}
