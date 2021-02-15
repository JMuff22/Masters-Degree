#include <iostream>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>


using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXf;
using Eigen::MatrixXf;

void myroots(int N, double *arr){
    MatrixXd A(N,N); // N x N double Matrix
    int n,m;
    int x = N-1;

    // for(int i=0;i< N;i++ ){
    //     cout << arr[i] << endl;
    // }

    for(n =0; n <=x; n++){
        for(m=0; m<=x; m++){
            if(n==m+1){
                A(n,m) = 1.0;
            }
            if(n<1){
                A(n,m) = -1.0*arr[m+1]/arr[0];
            }
        }
    }
    Eigen::ComplexEigenSolver<MatrixXd> ces;
    ces.compute(A);
    cout << "Companion Matrix is" << endl;
    cout << A << endl;
    cout << "Eigenvalues are " << endl;
    cout << ces.eigenvalues() << endl;
}

int main(){

    double p[] = {1,0,0,0,-1};
    // double p[] = {3,-2,-4};

    myroots(4,p); // INPUT p.length -1, p
    // myroots(2,p); // INPUT p.length -1, p
    return 0;
}

