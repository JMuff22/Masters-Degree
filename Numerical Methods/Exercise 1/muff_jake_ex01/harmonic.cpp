#include <iostream> 
#include <cmath>
#include <iomanip> 

void harmonic(){
    float k, s=0.0, a=1; //cast a to float
    for(k=1; k<=2097152; k++){ // 2097152 is the highest value k can go when using single precision floating point numbers
        s=s+a/k; // a is float here 
    }
    std::cout<< "The harmonic series sum= " << std::setprecision(10) << s << std::endl;

}

/* while loop implementation of the series up to 4e-7 precision. Achieves the same thing as the above function 
but takes longer. If I didn't know the characterisitics of a float in C/C++ then I would use this method. */
// void harmonic_while(){
//     float k, s=0.0, a=1; //cast a to float
//     k=1;
//     while (a/k > 1e-7){
//         s= s+a/k;
//         k++;
//         //std::cout<< s << " " << k << " " << a/k << std::endl;
//     }
//     std::cout<< "The harmonic series sum= " << s << std::endl;

// }

void harmonic_bunch(int N){
    float k, s=0.0, a=1;
    int i=0;
   while(i < 3000000){ //2097152
       for(k=i+1; k<=N+i; k++){ 
           s=s+a/k;
           
        }
        // std::cout<< "i = " << i << " s= " << s << std::endl;
        i=i+(N); //next bunch
        // std::cout << "i after bunch = " << i << std::endl;
    }
   std::cout<< "N = " << N << " Sum = " << s << std::endl;   
}



int main() {

    std::cout << "---Part A ---" << std::endl;
    harmonic();
    std::cout << "---Part B ---" << std::endl;
    // harmonic_while();
    std::cout << "N=50" << std::endl;
    harmonic_bunch(50);
    std::cout << "N=100" << std::endl;
    harmonic_bunch(100);
    std::cout << "N=500" << std::endl;
    harmonic_bunch(500);

}



