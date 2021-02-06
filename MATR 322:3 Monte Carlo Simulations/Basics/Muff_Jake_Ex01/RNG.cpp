#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random> // http://www.cplusplus.com/reference/random/
#include <fstream>


#include "rng.h"

double lcg_arr(int z, int N_arr){
    int a, c, m;
    m = 113829760;
    c=7371;
    a=3557181;
    double x[N_arr];
    for(int i=0; i<=N_arr; i++){
        x[i] = (a*lcg_s+c) %m ;
        lcg_s=x[i];
    }

    return x[z]/m;
}

double pm_arr(int z, int N_arr){
    int a = 16807;
    int q = 127773;
    int r = 2836;
    int m = 2147483647;
    
    long k;
    double ans[N_arr];
    

    double x[N_arr];
    for(int i=0; i<=N_arr; i++){
        k = pm_s / q;
        x[i] = a *(pm_s - k*q) - r*k;
        if(x[i] < 0){
        x[i] += m;
        }
        ans[i] = (1.0/m) * (x[i]);
    }

    

    return ans[z];
}

double MT_arr(int z, int N_arr){
    double x[N_arr];
    for(int i=0; i<=N_arr; i++){
        x[i] = genrand_real3();
    }

    

    return x[z];
}

void plot_lcg(int N_arr){
    double r0, r1;
    std::ofstream datafile1;
    datafile1.open ("x_lcg_1000.txt");
    std::ofstream datafile2;
    datafile2.open ("y_lcg_1000.txt");        
    for(int i=0; i<=N_arr; i++){

        if(i%2 ==0){
            r0 = lcg_arr(i,N_arr);
            datafile1 << i << " " <<  r0 << std::endl;

        }

        

        if(i%2 !=0){
            r1 = lcg_arr(i,N_arr);
            datafile2 << i << " " << r1 << std::endl;
        
        }

    }
    datafile1.close();
    datafile2.close();

}

void plot_pm(int N_arr){
    double r0, r1;
    std::ofstream datafile1;
    datafile1.open ("x_pm_1000.txt");
    std::ofstream datafile2;
    datafile2.open ("y_pm_1000.txt");        
    for(int i=0; i<=N_arr; i++){

        if(i%2 ==0){
            r0 = pm_arr(i,N_arr);
            datafile1 << i << " " <<  r0 << std::endl;

        }

        

        if(i%2 !=0){
            r1 = pm_arr(i,N_arr);
            datafile2 << i << " " << r1 << std::endl;
        
        }

    }
    datafile1.close();
    datafile2.close();

}

void plot_MT(int N_arr){
    double r0, r1;
    std::ofstream datafile1;
    datafile1.open ("x_mt_1000.txt");
    std::ofstream datafile2;
    datafile2.open ("y_mt_1000.txt");        
    for(int i=0; i<=N_arr; i++){

        if(i%2 ==0){
            r0 = MT_arr(i,N_arr);
            datafile1 << i << " " <<  r0 << std::endl;

        }

        

        if(i%2 !=0){
            r1 = MT_arr(i,N_arr);
            datafile2 << i << " " << r1 << std::endl;
        
        }

    }
    datafile1.close();
    datafile2.close();

}



int main(){
    double a,b,c;
    seed_lcg(15);   //Put a seed into LCG
    a=rand_lcg();   //Get a value from LCG
    seed_pm(7894);   //Put a seed into PM
    b=rand_pm();   //Get a value from PM
    init_genrand(431);   //The Mersenne twister built in function
    c=genrand_real3();   //The Mersenne twister built in function
    // printf ("LCG value: \%8.5f; Park-Miller value: \%8.5f; Mersenne twister: \%8.5f; \n", a,b,c); 
    std::cout << "LCG value: " << a << "; Park-Miller value: " << b << "; Mersenne twister: " << c << ";" << std::endl;

   // std::cout << "interval lcg= " << rand_lcg_interval() << std::endl;
    //std::cout << "interval pm= " << rand_pm_interval() << std::endl;


    // double x_new = 431;
    // double x=0;
    // long long  interval_count=0;

    // while (x != x_new){ // calculates the repeat interval for the mersenne twister but takes long to computer due to such a high period. 
    //     x = genrand_real3();
    //     interval_count +=1;
    // }
    // std::cout << "interval MT= " << x << std::endl;

    plot_lcg(1000);
    plot_pm(1000);
    plot_MT(1000);


    return 0;

}


