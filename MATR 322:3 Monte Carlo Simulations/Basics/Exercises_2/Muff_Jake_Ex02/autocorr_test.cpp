#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <random>

#include "rng.h"

using namespace std;
ofstream ofile;  
   
int main(int argc, char* argv[])
{
    //cout << "hello World1" << endl;
    cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
  
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 

    int n;
    char *outfilename;
     double MC_mean = 0.;      double MC_mean_sq=0.;
     long s;
     s=-7895;
    // invers_period = (1.0/RAND_MAX)

     if( argc <= 2 ){
       cout << "error " << argv[0] << 
	 " input output file and iterations on same line i.e ./a example.dat 10 " << endl;
       exit(1);
     }
     else{
       outfilename=argv[1];
     }
     ofile.open(outfilename); 
     // n = number of iterations specified in input changed to int using atoi
     n = atoi(argv[2]);
     double *X;  
     X = new double[n];
     for (int i = 0;  i < n; i++){
           // double x = RandomNumberGenerator(gen); // Mersenne Twister 
           // double x = double(rand())*invers_period;  // rand()
           // double x = double(ran0(&s)); //PM
           //x = double(rand_lcg()); // LCG
           double x = lcg_shuffle(&s); // LCG Shuffled
           X[i] = x;
           MC_mean += x;
           MC_mean_sq += x*x;
     }
     double Mean = MC_mean/((double) n );
     MC_mean_sq = MC_mean_sq/((double) n );
     double Variance = MC_mean_sq-Mean*Mean;

     // computing autocorrelation
     double *autocor;  
     autocor = new double[n];
     for (int j = 0; j < n; j++){
       double sum = 0.0;
       for (int k = 0; k < (n-j); k++){
	 sum  += (X[k]-Mean)*(X[k+j]-Mean); 
       }
       autocor[j] = sum/Variance/((double) n );
       ofile << setiosflags(ios::showpoint | ios::uppercase);
       ofile << setw(15) << setprecision(8) << j;
       ofile << setw(15) << setprecision(8) << autocor[j] << endl;
     }
     ofile.close();  // close output file
     return 0;
} 