#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>

#include "rng.h"

using namespace std;


int main(){

    // double invers_period = 1./RAND_MAX; 
    long s;
    s=7895;
    // cout << RAND_MAX << endl;
    // cout << invers_period << endl;
    srand(time(NULL));
    int n =10;
    for (int i = 0;  i < n; i++){
           //double x = double(rand())*invers_period; 
           //double x = double(ran0(&s));
           double x = double(rand_lcg());
           cout << x << endl;
     }



    return 0;
}