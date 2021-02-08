program devrandom

  implicit none
  integer,parameter :: LMASK =  2147483647, LUN=676767
  integer,parameter :: bk=selected_int_kind(6)
  character (len=80) :: argu,rdev='/dev/urandom'
  integer :: i,n,nr,is,iter
  integer,allocatable :: rn(:)

  call get_command_argument(0,argu)

  if (command_argument_count()/=2) then
     call get_command_argument(0,argu)
     write(0,'(a,a,a)') 'Usage: ',trim(argu),' nr iter'
     stop
  endif
  
  call get_command_argument(1,argu) ;read(argu,*) nr
  call get_command_argument(2,argu) ;read(argu,*) iter
  allocate(rn(nr))

  open(LUN,file=rdev,form='unformatted',access='stream',action='read',iostat=is)
  if (is/=0) then
     write(0,'(a,a)') 'Error opening file ''',trim(rdev),'''.'
     stop
  end if

  do i=1,iter
     read(LUN,iostat=is) rn
     if (is/=0) print *,'iostat',is
     print '(1000(2i12,4x))',(rn(n),iand(rn(n),LMASK),n=1,nr)
  end do

  stop
end program devrandom
