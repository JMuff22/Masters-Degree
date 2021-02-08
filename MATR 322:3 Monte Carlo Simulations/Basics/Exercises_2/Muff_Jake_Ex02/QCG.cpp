#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random> // http://www.cplusplus.com/reference/random/
#include <fstream>


#include "rng.h"


int main(){
    double a;
    seed_qcg(15);   //Put a seed into QCG
    a=rand_qcg();   //Get a value from QCG
    std::cout << "qcg value: " << a << std::endl;

   std::cout << "interval qcg= " << rand_qcg_interval() << std::endl;




    return 0;

}


