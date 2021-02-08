program rmainf
  implicit none
  integer,parameter :: rk=selected_real_kind(10,50)
  
  real(rk) :: r1,r2
  integer :: seed,nmax,n,i
  character(len=80) :: argu
  real(rk),external :: myrand
  integer,parameter :: DMAX=100
  integer :: dist(0:DMAX)

  call getarg(1,argu); read(argu,*) seed 
  call getarg(2,argu); read(argu,*) nmax
  dist=0
  do n=1,nmax
     r1=myrand(seed)
     r2=myrand(seed)
     i=int(r1*DMAX); dist(i)=dist(i)+1
     i=int(r2*DMAX); dist(i)=dist(i)+1
     print '(2f15.12)',r1,r2
  end do

  do i=0,DMAX
     write(10,*) i,dist(i)
  end do
  stop
end program rmainf
