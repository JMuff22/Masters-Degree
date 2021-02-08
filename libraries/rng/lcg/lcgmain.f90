program lcgmain
  implicit none
  integer,parameter :: ik=selected_int_kind(15),&
                     & rk=selected_real_kind(10,40)
  integer :: i,imax,iargc
  real(rk) :: x,y
  integer(ik) :: seed
  character(len=80) :: argu
  real(rk) :: lcg
  integer :: getseed

  call getarg(1,argu); read(argu,*) imax
  call getarg(2,argu); read(argu,*) seed
  if (seed<=0) seed=getseed()
  write(0,'(a,i10)') 'Seed ',seed

  do i=1,imax
     x=lcg(seed)
     y=lcg(seed)
     write(6,*) x,y
  end do

end program lcgmain
