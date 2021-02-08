!------------------------------------------------------!
!                                                      !
!  Get the RNG seed from /dev/urandom device.          !
!                                                      !
!  In order to get positive seed the most              !
!  significant bit in the number read from the         !
!  device is cleared (by anding it with LMASK).        !
!                                                      !
!  NOTE: Routine uses the default integer type.        !
!                                                      !
!  If the device can not be opened or read routine     !
!  falls back to calculating seed from the current     !
!  time.                                               !
!                                                      !
!  Note that stream i/o is used which is a Fortran     !
!  2003 feature.                                       !
!                                                      !
!  Input parameters:                                   !
!    info : integer, if /=0 print info to stdout       !
!    file : integer, 0: use /dev/urandom               !
!                    1: use /dev/random                !
!                                                      !
!  Generating a large amount of random numbers using   !
!  /dev/random may be slow because quality of random   !
!  bits from this device is guaranteed and system may  !
!  have to wait while enough 'entropy' is collected    !
!  from network traffic, keyboard, mouse, etc.         !
!                                                      !
!  A.Kuronen, antti.kuronen@helsinki.fi, 2008-2010     !
!                                                      !
!------------------------------------------------------!

integer function getseed(info,file)
  implicit none
  integer,intent(in) :: info,file
  integer :: t(8),rn,is
  integer,parameter :: LMASK=huge(rn) ! = 0111...111
  integer,parameter :: LUN=676769
  character (len=80) :: rdev0='/dev/urandom',rdev1='/dev/random',rdev
  logical :: openok,readok

  openok=.true.
  readok=.true.

  if (file==0) then
     rdev=rdev0
  else
     rdev=rdev1
  end if
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
     rn=iand(rn,LMASK) ! Make it positive, i.e. zero the leftmost bit
     if (info/=0) write(6,'(a,a,a,i0)') 'Seed from ',trim(rdev),': ',rn
  else
     call date_and_time(values=t)
     rn=t(7)+60*(t(6)+60*(t(5)+24*(t(3)-1+31*(t(2)-1+12*t(1)))))+t(8)
     if (info/=0) write(6,'(a,i12)') 'Seed from time:',rn
  end if

  getseed=rn
  return
end function getseed
