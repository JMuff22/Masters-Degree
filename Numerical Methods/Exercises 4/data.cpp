#include <iostream>
#include <math.h>
#include <fstream>


double func(double x, double mu){
    double a,b,c,d,f;
    a = -1.0 * (1/(mu-1));
    // std::cout << a << std::endl;
    b = mu*x-mu+1;
    c = (1.0/(mu-1));
    if(b<0){
        d = -1.0*pow(abs(b),c);

    }
    else{
        d = pow(b,c);
    }
    // std::cout << b << std::endl;
    
    // std::cout << c << std::endl;
    // std::cout << pow(x, a) << std::endl;
    // std::cout << d<< std::endl;


    f = pow(x, a)*d;
    // std::cout << f << std::endl;
    return f;
}

int main(){
    std::ofstream myfile;
    myfile.open("data_32.txt");

    double i = 0.3;
    double step = 0.001;
    while(i < 1){
        myfile << i << " " <<  func(i, 3.2) << std::endl;
        std::cout << i << " " << func(i, 3.2) << std::endl;
        i = i + step;

    }
    myfile.close();
    // std::cout << func(0.3, 2.5) << std::endl;

    return 0;
}