#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random> // http://www.cplusplus.com/reference/random/
#include <fstream>
#include <iomanip>


#include "rng.h"







int main(){
    int n=1e6;

    long s;
    s=7895;

    // for(int i=0; i<n; i++){
    //     std::cout << ran0(&s) << std::endl;


    // }
    double bins =100;
    double binw = 1/bins;

    std::ofstream datafile1;
    datafile1.open ("lcg_arr.txt");
    std::ofstream datafile2;
    datafile2.open ("pm_arr.txt");
    std::ofstream datafile3;
    datafile3.open ("MT_arr.txt");
    std::ofstream datafile4;
    datafile4.open ("qcg_arr.txt");  

    for (int i=0; i<n; i++){
        datafile1 << lcg_arr(i,n) << std::endl;
        datafile2 << ran0(&s) << std::endl;
        datafile3 << MT_arr(i,n) << std::endl;
        datafile4 << qcg_arr(i,n) << std::endl;
    }
   
        
        



    datafile1.close();
    datafile2.close();
    datafile3.close();
    datafile4.close();
    

    //chisquare(x,100);

    return 0;

}


