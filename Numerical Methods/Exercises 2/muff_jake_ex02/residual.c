

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void dgemm_(char *TRANSA, char *TRANSB, int *M, int *N, int *K,
 	double *ALPHA, double *A, int	*LDA, double *B, int *LDB, double	*BETA,
  double *C, int *LDC);	

void residual(int m){ 
  int n, i,j,c1,c2,*pivot,ok;
  double *A, *b, *x, *b_2, *res;
  double *A_2;
  
  FILE *file;
  file = fopen("matrix6", "r");
  if(file == NULL){
    printf("Error! Cannot find file\n");
    exit(1);
  }
  fscanf(file,"%d",&n);
  printf("The rank is = %d \n",n);
  printf("Solving Ax=b system...\n");

  A=(double *)malloc((size_t)n*n*sizeof(double));
  b=(double *)malloc((size_t)n*sizeof(double));
  x=(double *)malloc((size_t)n*sizeof(double));
  if (A==NULL || b==NULL || x==NULL){
	printf("Malloc failed!\n");
  } 

  A_2 = (double *)malloc((size_t)n*n*sizeof(double));
  b_2=(double *)malloc((size_t)n*sizeof(double));
  res=(double *)malloc((size_t)n*sizeof(double));
  if (A_2==NULL || b_2==NULL || res==NULL){
	printf("2nd Malloc failed!\n");
  } 

  pivot=(int *)malloc((size_t)n*sizeof(int));


  for (i=0;i<n;i++) {
	for (j=0;j<n;j++) {
            fscanf(file, "%lg",&(A[j*n+i]));
        }
  }

  printf("Matrix A read..\n");
  printf("Reading Matrix b..\n");


  for (i=0;i<n;i++){
    fscanf(file,"%lg",&(b[i]));
  }



  printf("Matrix b read..\n");
  fclose(file);

  printf("A\n");
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++){
       printf("%12.8g ",A[j*n+i]);
       A_2[j*n+i] = A[j*n+i]; //copy A because a is changed by dgesv
    }
    printf("\n");
    }
  printf("\nb\n");
  for (i=0;i<n;i++){ 
    printf("%12.8g ",b[i]);
    b_2[i] = b[i]; //copy b because b is changed be dgesv
  }
  printf("\n");
  printf("\n FILE READING DONE\n");

  c1=n;
  c2=1;
  
  dgesv_(&c1, &c2, A, &c1, pivot, b, &c1, &ok);      
  
  printf("x\n");
  for (i=0;i<n;i++){
    x[i] = b[i]; // degsv overwrites and outputs b as the solution. 
    printf("%12.8g ", x[i]);
  }
  printf("\n");
  printf("ok = %d\n", ok);


  //////////////////////

  //reallocate with size 0;

  free(A);
  free(b);
  free(pivot);

  // printf("free b mem alloc\n");
  // for (i=0;i<n;i++){ 
  //   printf("%12.8g ",b[i]);
  // }


  printf("\n----------\n");
  printf("Calculating residual Ax - b");
  printf("\n----------\n");

  printf("A_2\n");
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) printf("%12.8g ",A_2[j*n+i]);
    printf("\n");
    }

  printf("x\n");
  for (i=0;i<n;i++){
    printf("%12.8g ", x[i]);
  }

  printf("\nb\n");
  for (i=0;i<n;i++){ 
    printf("%12.8g ",b_2[i]);
  }

  // res = A*x - b. A = n columns, n rows. b and x = n rows, 1 column
  char *chn = "N";
  double alpha, beta;
  alpha =1.0;
  beta = -1.0;
  // dgemm(N, N, rows of A and b, columns of x and b, columns of A and rows of x, )
  dgemm_(chn, chn, &c1, &c2, &c1, &alpha, A_2, &c1, x, &c1, &beta, b_2, &c1); //prototyping

  printf("\n residual\n");
  for (i=0;i<n;i++){
   printf("%12.8g ", b_2[i]);
   res[i] = b_2[i]; //assign b_2 to res due to dgemm overwriting b_2 
  } 

  printf("\n ----NORM --- \n");
  double norm;
  double sum =0;
  int location =0;
  if(m ==0){ //m= 0 is m inf case
    for(i =1; i < n; i++){
      if(fabs(res[i]) > res[location]){
        location = i;
      }
    }
    printf("Max element is %lg \n", res[location]);
      
  }

  else{
    for(i =1; i<=n; i++){
      sum+= pow(fabs(res[i]), m);

    }
    double p = 1.0/m;
    norm = pow(sum,p);
    printf("norm- %d is %lg \n", m, norm);
  }
}

int main()
{
  // int N;
  // double A,b,x;
  printf("****For m= %d, norm - %d calculated ****\n", 1, 1);
  residual(1);
  printf("****For m= %d, norm - %d calculated****\n", 2, 2);
  residual(2);
  printf("****For m= 0, norm - inf calculated****\n");
  residual(0); //0 = inf

  return 0;
}

