

all:	harmonic_kahan.cpp ex2_p3.c residual.c
		#clang++ -std=c++17 -Wall -pedantic harmonic_kahan.cpp -o harmonic_kahan
		g++ -std=c++17 -Wall -pedantic harmonic_kahan.cpp -o harmonic_kahan
		gfortran -o ex2_p3 ex2_p3.c -llapack 
		gfortran -o residual residual.c -llapack -Llapack/lapackf90/src


harmonic_kahan:	harmonic_kahan.cpp
		#clang++ -std=c++17 -Wall -pedantic harmonic_kahan.cpp -o harmonic_kahan
		g++ -std=c++17 -Wall -pedantic harmonic_kahan.cpp -o harmonic_kahan

ex2_p3: ex2_p3.c
		gfortran -o ex2_p3 ex2_p3.c -llapack  

residual: residual.c
		gfortran -o residual residual.c -llapack -Llapack/lapackf90/src
