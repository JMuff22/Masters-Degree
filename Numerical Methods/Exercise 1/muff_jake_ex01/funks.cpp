#include <iostream> 
#include <cmath>
#include <fstream>
#include <iomanip>


// function to find factorial of given number 
unsigned int factorial(unsigned int n) 
{ 
    if (n == 0) 
        return 1; 
    return n * factorial(n - 1); 
} 

double funks1(double x){
    double f1;
    f1 = (cos(x)-1)/pow(x,2);

    return f1;
}

double funks2(double x){
    double f2;
    f2 = (exp(x) - exp(-1.0*x))/ (2*x);

    return f2;
}

void funks(double x){
    double f1, f2;
    f1 = (cos(x)-1)/pow(x,2);
    f2 = (exp(x) - exp(-1.0*x))/ (2*x);

    std::cout << "For x=" << x << " f1=" << f1 << " f2=" << f2 << std::endl;
}

double funks_Taylor(double x){ 
    double f1_approx=-0.5;
    double f2_approx=1.0;
    double err_f1=1;
    double err_f2=1;


    for(int n=1; n<6; n++){ // max n can be 5 before precision lost
    f1_approx += pow(-1,n+1) * (pow(x,2*n))/(factorial(2*n+2));
    err_f1 = f1_approx - funks1(x);
    }
   

    for(int n=1; n<6; n++){ // max n can be 5 before precision lost
    f2_approx += (pow(x,2*n))/(factorial(2*n+1));
    err_f2 = f2_approx - funks1(x);
    }

    std::cout << "f1_approx  ( "<< x << ")= " << std::setprecision(10) <<  f1_approx << std::endl;
    std::cout <<  "f2_approx( "<< x << ")= " << std::setprecision(10) <<  f2_approx << std::endl;
  
    // f1_approx =        // -1/2! + x^2 /4! - x^4 / 6! + ...
    // f2_approx =         // 1+ x^2 /3! + x^4 / 5! + ...
    return 0;
}

double funks_Taylor_f1(double x){ 
    double f1_approx=-0.5;
    double err_f1=1;


    // while (abs(err_f1) > 1e-5){
    // f1_approx += pow(-1,n_1+1) * (pow(x,2*n_1))/(factorial(2*n_1+2));
    // err_f1 = f1_approx - funks1(x);
    // n_1+=1;
    // }
    for(int n=1; n<6; n++){ // max n=5 (order 10) before precision lost
    f1_approx += pow(-1,n+1) * (pow(x,2*n))/(factorial(2*n+2));
    err_f1 = f1_approx - funks1(x);
    }
    
    return f1_approx;
}

double funks_Taylor_f2(double x){ 
    double f2_approx=1.0;
    double err_f2=1;

    // while (abs(err_f2) > 1e-5){
    // f2_approx += (pow(x,2*n_2))/(factorial(2*n_2+1));
    // err_f2 = f2_approx - funks2(x);
    // n_2+=1;
    // }
    for(int n=1; n<6; n++){ // max n=5 (order 10) before precision lost
    f2_approx += (pow(x,2*n))/(factorial(2*n+1));
    err_f2 = f2_approx - funks2(x);
    }

    return f2_approx;
}




int main(){

double x;
//writing to file. Commented out because it causes increaed run time. 
// std::ofstream datafile;
// datafile.open ("dat.txt");
// datafile << "a" << " " << "f1" << " " << "f2" << " " << "f1_approx" << " " << "f2_approx" << std::endl;
// for(int i=-50; i<=50; i++){
//     double a = i/ 10.0;
//     std::cout << a << std::endl;
//     datafile << a << " " << funks1(a) << " " << funks2(a)  << " " << funks_Taylor_f1(a) << " " << funks_Taylor_f2(a) <<  std::endl;
    
// }
// datafile.close();

std::cout << "Give x at or near 0: " << std::endl;
std::cin >> x; 
funks(x);
funks_Taylor(x);

/*
Give x: 
0.1
For x=0.1 f1=-0.499583 f2=0.0100167

Give x: 
-0.1
For x=-0.1 f1=-0.499583 f2=0.0100167


Give x: 
0
For x=0 f1=nan f2=0

Give x: 
0.00001
For x=1e-05 f1=-0.5 f2=1e-10


*/
    return 0;
}