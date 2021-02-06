#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random> // http://www.cplusplus.com/reference/random/
#include <fstream>


double const pi_actual = 3.14159265359;

double buffon_needle(int N,int n,double *pi_est_avg, double *err_avg);




int main(){

std::ofstream datafile; // outputting error averages to file 
datafile.open ("dat1.txt");
double pi_est_avg, err_avg ;

for(double i=1; i<=7; i++){
    double a;
    a = pow(10,i);
    datafile << a << " " << buffon_needle(100,a, &pi_est_avg, &err_avg) << std::endl;
    std::cout << "For " << a << " needles " << "pi_est_avg= " << pi_est_avg << " error average= " << err_avg << std::endl;

}
datafile.close();

// for(double i =1; i<=1e7; i++){
//     buffon_needle(100,i, &pi_est_avg, &err_avg);
//     std::cout << err_avg << std::endl;
//     if(err_avg <  0.0001){
//         std::cout << i << std::endl;
//         break;
//     }
// }

return 0;    
}

double buffon_needle(int N,int n, double *pi_est_avg, double *err_avg){
    double a, k,y;
    double l = 2;
    double d = 10;
    double x =0;
    double pi_est;
    double x_avg;
    double err_sum=0;
    // double err_avg;
    double pi_est_sum =0;
    double x_sum =0;
    // double pi_est_avg;

    std::mt19937 rng( std::random_device{}() ); // Mersenne Twister 199937
    std::uniform_real_distribution<> dist_1(0, pi_actual/2);
    std::uniform_real_distribution<> dist_2(0, d/2);

for(int i=0; i<N; i++){



    for (int i=0; i<n; i++)
    {
        k = dist_1(rng);     // random angle between 0 and pi/2
        a = dist_2(rng);       // random a between 0 and d/2 

        y = (l/2) * sin (k);



        if (a<=y)                                    
        {
            x++;
        }

    }
    if(x==0){ // catch divide by 0 errors (leads to the sums = inf)
        pi_est=0;
    }
    else{
         pi_est = ((n/x)*2*l)/d;
    }
   
    pi_est_sum += pi_est; 
    err_sum += abs(pi_est - pi_actual);
    // std::cout << "Sim " << i<< ": " << x << " needle lands on a line out of " << n << " needles"  << std::endl;
    // std::cout.precision(10); 
    // std::cout << "Pi= " << pi_est_sum << std::endl;
    x_sum += x;
    x=0;

}

x_avg = x_sum/N; 
*err_avg = err_sum/N;
*pi_est_avg = pi_est_sum/N;

// std::cout << "Number of Simulations= " << N << std::endl;
// std::cout << "Number of Needles dropped= " << n << std::endl;
// std::cout << "Total Number of Positive trials= " << x_sum << std::endl;
// std::cout << "Average Number of Positive trials= " << x_avg << std::endl;
std::cout.precision(10); 
// std::cout << "Estimate of pi= " << pi_est_avg << std::endl;
// std::cout << "Error average= " << err_avg << std::endl;




return *err_avg; 
}
