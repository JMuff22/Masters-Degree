

all:	buffon.cpp RNG.cpp 

buffon: buffon.cpp
		# g++ helloworld.cpp -I/psth/to/include -o helloworld -L/path/to/libraries
		clang++ -std=c++17 -Wall -pedantic buffon.cpp -o buffon
rng: RNG.cpp
		clang++ -std=c++17 -Wall -pedantic RNG.cpp -o RNG
		gcc rng.h

