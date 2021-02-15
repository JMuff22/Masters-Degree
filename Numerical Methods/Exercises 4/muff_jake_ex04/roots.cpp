#include <iostream>
#include <math.h>

#define eps 0.01

const double pi = 3.14159265359;


double func1(double x);
double f1prime(double x);
void bisec_f(double a, double b);
void newton_f(double x0);
double newton_g(double x0, double B);



int main (){



    // bisec_f(0,1);
    // newton_f(0.3);

    // newton_g(0,0.1);
    std::cout << "----Problem 2----" << std::endl;
    std::cout << "Root for B= " << 0.1 << " root= " << newton_g(1,0.1) << " for initial guess " << 1 << std::endl;
    std::cout << "Root for B= " << 1 << " root= " << newton_g(1,1) << " for initial guess " << 1 << std::endl;
    std::cout << "Root for B= " << 10 << " root= " << newton_g(0.14,10) << " for initial guess " << 0.14 << std::endl;
    std::cout << "Root for B= " << 100 << " root= " << newton_g(0.14,100) << " for initial guess " << 0.14 << std::endl;
    // std::cout << newton_g(0.14,10) << std::endl; //have to use small initial guess as the nature of the functions means it easily exceeds double size limit or enters infinite loop. 
    // std::cout << newton_g(0,10) << std::endl;    


}






double func1(double x){
    double f;
    f= sin( 3*pi * (pow(x,3))/(pow(x,2)-1))+0.5;
    //f=cos(x);
    

    return f;
}

double f1prime(double x){
    double f, num, denom;
    //f = (3*pi * pow(x,2) *(pow(x,2) -3) * cos((3*pi * pow(x,3) )/(pow(x,2)-1) ) )/((pow(x,2) -1)*(pow(x,2) -1) ) ;
    num = (3*pi * pow(x,2) *(pow(x,2) -3) * cos((3*pi * pow(x,3) )/(pow(x,2)-1) ) );
    denom = ((pow(x,2) -1)*(pow(x,2) -1) ) ;
    f= num/denom;
    return f;

}

void bisec_f(double a, double b){
    int iterations =0;
    if(func1(a) * func1(b) >=0.0){
        std::cout << "f(" << a << ") * f(" << b << ") = " << func1(a)*func1(b) <<" must be greater than or equal to 0" << std::endl;
        exit(1);
    }
    if(a > b){
        std::cout << "a must be less than b" << std::endl;
        exit(1);
    }
    double c = a;
    while(b-a >= eps){
        c = (a+b)/2;
        if (func1(c) == 0.0){
            break;
        }
        else if (func1(c)*func1(a) < 0){
            b=c;
        }
        else{
            a=c;
        }
        iterations++;
    }
    std::cout << "Iterations = " << iterations << std::endl;
    std::cout << "Root for f(x) using Bisection, f(x) =0 when x= " << c << std::endl;
}

void newton_f( double x0){
    double d = func1(x0) / f1prime(x0);
    double iterations =0;
    std::cout << "Begin newton method " << std::endl;
    std::cout << "x0" << " " << "d" << std::endl;
    std::cout << x0 << " " << d << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "x_i" << " " << "d"  << std::endl;


    while(abs(d) >= eps){
        d = func1(x0) / f1prime(x0);
        x0= x0-d;
        iterations++;
        std::cout << x0 << " " << d << std::endl;
    }
    std::cout << "-------------" << std::endl;
    std::cout << "end newton method " << std::endl;
    std::cout << "-------------" << std::endl;

    std::cout << "root is " << x0 << " after " << iterations << " iterations" << std::endl;

}

double newton_g( double x0, double B){
    double f, fprime;
    double iterations =0;
    int max_iter = 100;
    f = x0 + exp(-1.0*B*pow(x0,2))*cos(x0);
    fprime = -1.0*exp(-1.0*B*pow(x0,2)) *(sin(x0) + 2.0*B*x0*cos(x0) - exp(B*pow(x0,2)));
    double d = f/fprime;
    while(abs(d) >= eps){
        f = x0 + exp(-1.0*B*pow(x0,2))*cos(x0);
        fprime = -1.0*exp(-1.0*B*pow(x0,2)) *(sin(x0) + 2.0*B*x0*cos(x0) - exp(B*pow(x0,2)));
        d = f/fprime;
        x0= x0-d;
        iterations++;
        if(iterations == max_iter){
            std::cout << "Max iters reached" << std::endl;
            break;
        }
        // std::cout << x0 << " " << d << " " << iterations << std::endl;
    }
    // std::cout << "root is " << x0 << " after " << iterations << " iterations" << std::endl;
    return x0;
}
