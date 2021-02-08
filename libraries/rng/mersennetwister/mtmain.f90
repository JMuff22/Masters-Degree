
!
! Program showing the usage of getseed function and the Mersenne
! twister random number generator in module mtmod.
! The module was originally obtained from
! http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/VERSIONS/FORTRAN/mtfort90.f
!
! Modified slightly by A.Kuronen, 2008-2010
! 

program mtmain
  use defs
  use mtmod
  implicit none
  integer :: n,nr,info,file
  character(len=80) :: argu

  interface
     integer function getseed(info,file)
       integer,intent(in) :: info,file
     end function getseed
  end interface

  if (command_argument_count()/=1) then
     call get_command_argument(0,argu)
     write(0,'(a,a,a)') 'Usage: ',trim(argu),' nr'
     stop
  endif
  
  call get_command_argument(1,argu); read(argu,*) nr
  call sgrnd(getseed(0,0))
  do n=1,nr
     print *,grnd(),grnd()
  end do


  stop
end program mtmain
