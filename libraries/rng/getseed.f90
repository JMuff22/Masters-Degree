!program test
!  integer :: getseed,i
  
!  i=getseed()
!  write(0,*) i
!  stop
!end program test


function getseed()
  implicit none
  integer :: getseed
  integer :: t(8),i

  call date_and_time(values=t)
  !write(0,'(i4,i5)') (i,t(i),i=1,8)

  getseed=t(7)+60*(t(6)+60*(t(5)+24*(t(3)-1+31*(t(2)-1+12*t(1)))))+t(8)
  !getseed=t(8)

end function getseed
