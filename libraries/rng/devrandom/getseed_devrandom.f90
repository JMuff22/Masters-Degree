
!----------------------------------------------------!
!                                                    !
!  Get the RNG seed from /dev/urandom device.        !
!  In order to get positive seed the most            !
!  significant bit in the number read from the       !
!  device is cleared (by anding it with LMASK).      !
!                                                    !
!  If the device can not be opened or read           !
!  routine falls back to calculating seed from       !
!  the current time.                                 !
!                                                    !
!  Note that the stream access of a file is used     !
!  which is a Fortran 2003 feature.                  !
!                                                    !
!  A.Kuronen, antti.kuronen@helsinki.fi, 2008        !
!                                                    !
!----------------------------------------------------!

function getseed()
  implicit none
  integer :: getseed
  integer :: t(8),rn,is
  integer,parameter :: LMASK=2147483647
  integer,parameter :: LUN=676767
  character (len=80) :: rdev='/dev/urandom'
  logical :: openok,readok

  openok=.true.
  readok=.true.

  open(LUN,file=rdev,form='unformatted',access='stream',action='read',iostat=is)
  if (is/=0) then
     openok=.false.
     print *,'open',is
  else
     read(LUN,iostat=is) rn
     if (is/=0) then
        readok=.false.
     end if
  end if
  if (openok) close(LUN)

  if (openok.and.readok) then
     rn=iand(rn,LMASK)
     write(0,'(a,i12)') 'Seed from /dev/urandom:',rn
  else
     call date_and_time(values=t)
     rn=t(7)+60*(t(6)+60*(t(5)+24*(t(3)-1+31*(t(2)-1+12*t(1)))))+t(8)
     write(0,'(a,i12)') 'Seed from time:',rn
  end if

  getseed=rn

  return
end function getseed
