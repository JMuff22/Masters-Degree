
####################################
# GNU Fortran
####################################
F90=gfortran
FFLAGS=-O
LDFLAGS= 

####################################
# Intel Fortran compiler
####################################
#F90=ifort
#FFLAGS=-O3
#LDFLAGS=-O3

OBJ=defs.o  getseed_devrandom.o  mtfort90.o  mtmain.o

mtmain: $(OBJ)
	$(F90) $(LDFLAGS) -o $@ $^

mtmain.o: defs.o mtfort90.o getseed_devrandom.o
mtfort90.o: defs.o


%.o: %.f90
	$(F90) $(FFLAGS) -c $<


clean:
	rm -f *.o *.mod mtmain
