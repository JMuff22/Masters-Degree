#include <math.h> 
#include <iostream>
#include <new>
#include <random>
#include <fstream>

#include "rng.h"

void jacobi( double ** A, int n );
double jacobi_ret( double ** A, int n );
void **matrix_mem_alloc(int row, int col, int num_bytes);
double err_propag(int n, double dq);

std::ofstream ofile;  


int main(){

    std::cout << "Hello World" << std::endl;
    srand (time(NULL));


    int i, j, n = 3;

    // for(i =0; i < n; i++){
    //     std::cout << genrand_real3() << std::endl;
    // }
    double **matr;
    double a[3][3]   = { {1.0, 2.0, 3.0},
		  {4.0, 5.0, 6.0},
		  {7.0, 8.0, 9.0}}; 



    // memory for  inverse matrix 
    matr = (double **) matrix_mem_alloc(n, n, sizeof(double));   

    printf("\n\nInitial matrix a[][]:");      // print matrix a[][] 
    for(i = 0; i < n; i++) {
        printf("\n");
        for(j = 0; j < n; j++) {
            printf("%12.4f", a[i][j]);
        }
    }
    for(i = 0; i < n; i++) {                // transfer a[][] to matr[][] 
        for(j = 0; j < n; j++){
            matr[i][j] = a[i][j];

        }  

    }
    std::cout << std::endl;
    std::cout << "Final Matrix with diagonal values as eigenvalues" << std::endl;
    jacobi(matr,n);

    ofile.open("f_3_10.txt");
    double mean = 0.0;
    double mean_sq = 0.0;
    for(i =0; i < 100; i++){
        double f = err_propag(3,10);
        std::fixed;
        ofile << i << " " << f << std::endl;
        mean += f;
        mean_sq += f * f;
    }
    mean = mean/((double) 100);
    std::cout << "f statistics for N= " << 3 << " ,dq = " << 10 << " ,and random matrix between 0 and 100" << std::endl;
    std::cout << "Mean f = " << mean << std::endl;
    mean_sq = mean_sq/((double) 100);
    double STDev = sqrt(mean_sq-mean*mean);
    std::cout << "STD f = " << STDev << std::endl;

    //std::cout << err_propag(3,1) << std::endl;


    ofile.close();
}


void jacobi( double ** A,int n )
{


    int p, q;
    double eps = 1.0e-10;
    double max_count = (double) n * (double) n * (double) n;
    int count = 0;
    
    // first original max element
    double max = 0.0;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = i + 1; j < n; j++ ) {
            if ( fabs(A[i][j]) > max ) {
                max = fabs(A[i][j]);
                q = i;
                p = j;
                }
            }
        }

    double max_offdiag = max;
    while ( fabs(max_offdiag) > eps && (double) count < max_count ) {
        // find max element for each new matrix 
        double max_ele = 0.0;
        for ( int i = 0; i < n; i++ ) {
            for ( int j = i + 1; j < n; j++ ) {
                if ( fabs(A[i][j]) > max_ele ) {
                    max_ele = fabs(A[i][j]);
                    q = i;
                    p = j;
                }
            }
        }
        max_offdiag = max_ele;

        double s, c;
        if ( A[p][q] != 0.0 ) {
            double t, phi;
            phi = (A[q][q] - A[p][p])/(2*A[p][q]);
            if ( phi > 0 ) {
                t = 1.0/(phi + sqrt(1.0 + phi*phi));
            }    
            else {
            t = -1.0/( -phi + sqrt(1.0 + phi*phi));
            }
            c = 1/sqrt(1+t*t);
            s = c*t;
        } 
            else {
                c = 1.0;
                s = 0.0;
            }
        double a_pp, a_qq, a_ip, a_iq;
        a_pp = A[p][p];
        a_qq = A[q][q];
        // changing the matrix elements with indices p and q
        A[p][p] = c*c*a_pp + s*s*a_qq - 2.0*c*s*A[p][q];
        A[q][q] = s*s*a_pp + c*c*a_qq + 2.0*c*s*A[p][q]; 
        A[p][q] = 0.0; // setting = to 0.0 brute force
        A[q][p] = 0.0;
        // and then we change the remaining elements
        for ( int i = 0; i < n; i++ ) {
            if ( i != p && i != q ) {
                a_ip = A[i][p];
                a_iq = A[i][q];
                A[i][p] = c*a_ip - s*a_iq;
                A[p][i] = A[i][p];
                A[i][q] = c*a_iq + s*a_ip;
                A[q][i] = A[i][q];
            }
        }

        count++;
    }
    //std::cout << "iterations: " << count << "\n";

    for(int i = 0; i < n; i++) {
        printf("\n");
        for(int j = 0; j < n; j++) {
            printf("%12.4f", A[i][j]);
        }
    }

    printf("\n");


    return;
}

double jacobi_ret( double ** A,int n, int k, int l )
{


    int p, q;
    double eps = 1.0e-10;
    double max_count = (double) n * (double) n * (double) n;
    int count = 0;
    
    // first original max element
    double max = 0.0;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = i + 1; j < n; j++ ) {
            if ( fabs(A[i][j]) > max ) {
                max = fabs(A[i][j]);
                q = i;
                p = j;
                }
            }
        }

    double max_offdiag = max;
    while ( fabs(max_offdiag) > eps && (double) count < max_count ) {
        // find max element for each new matrix 
        double max_ele = 0.0;
        for ( int i = 0; i < n; i++ ) {
            for ( int j = i + 1; j < n; j++ ) {
                if ( fabs(A[i][j]) > max_ele ) {
                    max_ele = fabs(A[i][j]);
                    q = i;
                    p = j;
                }
            }
        }
        max_offdiag = max_ele;

        double s, c;
        if ( A[p][q] != 0.0 ) {
            double t, phi;
            phi = (A[q][q] - A[p][p])/(2*A[p][q]);
            if ( phi > 0 ) {
                t = 1.0/(phi + sqrt(1.0 + phi*phi));
            }    
            else {
            t = -1.0/( -phi + sqrt(1.0 + phi*phi));
            }
            c = 1/sqrt(1+t*t);
            s = c*t;
        } 
            else {
                c = 1.0;
                s = 0.0;
            }
        double a_pp, a_qq, a_ip, a_iq;
        a_pp = A[p][p];
        a_qq = A[q][q];
        // changing the matrix elements with indices p and q
        A[p][p] = c*c*a_pp + s*s*a_qq - 2.0*c*s*A[p][q];
        A[q][q] = s*s*a_pp + c*c*a_qq + 2.0*c*s*A[p][q]; 
        A[p][q] = 0.0; // setting = to 0.0 brute force
        A[q][p] = 0.0;
        for ( int i = 0; i < n; i++ ) {
            if ( i != p && i != q ) {
                a_ip = A[i][p];
                a_iq = A[i][q];
                A[i][p] = c*a_ip - s*a_iq;
                A[p][i] = A[i][p];
                A[i][q] = c*a_iq + s*a_ip;
                A[q][i] = A[i][q];
            }
        }

        count++;
    }
    //std::cout << "iterations: " << count << "\n";


    return A[k][l];
}

// function allocate size of matrix. Adapted from Num Recipes.
void **matrix_mem_alloc(int row, int col, int num_bytes)
  {
  int      i, num;
  char     **pointer, *ptr;

  pointer = new(std::nothrow) char* [row];
  i = (row * col * num_bytes)/sizeof(char);
  pointer[0] = new(std::nothrow) char [i];
  ptr = pointer[0];
  num = col * num_bytes;
  for(i = 0; i < row; i++, ptr += num )   {
    pointer[i] = ptr; 
  }

  return  (void **)pointer;

  }

double err_propag(int n, double dq){
    int i, j;
    double **rand_matr;
    double **pert_matr;
    double a[n][n];

      for(i = 0; i < n; i++) {                // transfer a[][] to matr[][] 
        for(j = 0; j < n; j++){
            a[i][j] = genrand_real3()*100; //mersenne twister PRNG from "rng.h"
            // random real numbers between (0 and 1)*100 = 0 and 100

        }  

    }
    printf("\n\nRandom matrix a[][]:");      // print matrix a[][] 
    for(i = 0; i < n; i++) {
        printf("\n");
        for(j = 0; j < n; j++) {
            printf("%12.4f", a[i][j]);
        }
    }
    rand_matr = (double **) matrix_mem_alloc(n, n, sizeof(double));   
    for(i = 0; i < n; i++) {                // transfer a[][] to matr[][] 
        for(j = 0; j < n; j++){
            rand_matr[i][j] = a[i][j];

        }  

    }
    std::cout << std::endl;
    std::cout << "Eigenvalues of random Matrix" << std::endl;
    jacobi(rand_matr,n);
    std::cout << "Selecting random element from a[][]" << std::endl;
    int i_r = rand() % n;
    int j_r = rand() % n;
    std::cout << "Random Element is: a[ " << i_r+1 << "][ " << j_r+1 << "]= " << a[i_r][j_r] << std::endl;
    std::cout << "Perturbing Random Element" << std::endl;
    a[i_r][j_r] = a[i_r][j_r] + dq; //pertubring
     printf("\n\nPerturbed random matrix a[][]:");      // print matrix a[][] 
    for(i = 0; i < n; i++) {
        printf("\n");
        for(j = 0; j < n; j++) {
            printf("%12.4f", a[i][j]);
        }
    }

    pert_matr = (double **) matrix_mem_alloc(n, n, sizeof(double));
     for(i = 0; i < n; i++) {                // transfer a[][] to matr[][] 
        for(j = 0; j < n; j++){
            pert_matr[i][j] = a[i][j];

        }  

    }
    std::cout << std::endl;
    std::cout << "Eigenvalues of perturbed random Matrix" << std::endl;
    jacobi(pert_matr,n);
    std::cout << std::endl;
    std::cout << "Errors" << std::endl;
    std::cout << jacobi_ret(pert_matr,n, 0,0) << " " << jacobi_ret(rand_matr,n, 0,0) << " " << jacobi_ret(pert_matr,n, 0,0) - jacobi_ret(rand_matr,n, 0,0) << std::endl;
    std::cout << jacobi_ret(pert_matr,n, 1,1) << " " << jacobi_ret(rand_matr,n, 1,1) << " " << jacobi_ret(pert_matr,n, 1,1) - jacobi_ret(rand_matr,n, 1,1) << std::endl;
    std::cout << jacobi_ret(pert_matr,n, 2,2) << " " << jacobi_ret(rand_matr,n, 2,2) << " " << jacobi_ret(pert_matr,n, 2,2) - jacobi_ret(rand_matr,n, 2,2) << std::endl;

    double f, delta_lam_norm, lambda_norm;
    double u[n], y[n];
    // initialize
    for (int i = 0; i < n; ++i) {
        u[i] = jacobi_ret(pert_matr,n, i,i) - jacobi_ret(rand_matr,n, i,i);
        //std::cout << u[i] << std::endl;
    }
    double u_accum = 0.;
    for (int i = 0; i < n; ++i) {
        u_accum += u[i] * u[i];
    }
    delta_lam_norm = sqrt(u_accum);


    // initialize
    for (int i = 0; i < n; ++i) {
        y[i] = jacobi_ret(rand_matr,n, i,i);
        //std::cout << u[i] << std::endl;
    }
    double y_accum = 0.;
    for (int i = 0; i < n; ++i) {
        y_accum += y[i] * y[i];
    }
    lambda_norm = sqrt(y_accum);
    
    f = delta_lam_norm/ (lambda_norm * dq);






    


    return f;
}