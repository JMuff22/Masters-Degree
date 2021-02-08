program data_and_gaussian

  implicit none
  integer,parameter :: rk=selected_real_kind(10,40) ! Double precision
  real(rk) :: func,gaussianrand,sigma,x,y
  integer :: n,np,seed,fsel,getseed
  integer :: iargc
  character(len=80) :: argu

  call getarg(1,argu); read(argu,*) np
  call getarg(2,argu); read(argu,*) sigma
  call getarg(3,argu); read(argu,*) fsel
  call getarg(4,argu); read(argu,*) seed

  if (seed<=0) seed=getseed()
  write(0,'(a,i10)') 'Seed ',seed

  do n=1,np
     x=n
     y=func(x,fsel)+sigma*gaussianrand(seed)
     write(6,'(3g16.8)') x,y,sigma
  end do
  stop
end program data_and_gaussian


  
function func(x,fsel)
  implicit none  
  integer,parameter :: rk=selected_real_kind(10,40) ! Double precision
  real(rk) :: func
  real(rk),intent(in) :: x
  integer,intent(in) :: fsel
  real(rk),parameter :: a=0.1,b=1.0,c=0.0
  real(rk),parameter :: xg=128.0,sigmag=20.0

  select case (fsel)
     case (1)
        func=x
     case (2)
        func=a*x**2+b*x+c
     case (3)
        func=exp(-(x-xg)**2/(2*sigmag**2))
     case (4)
        func=1/(1+((x-512)/10)**2)
     case default
        func=1
     end select

  return
end function func
