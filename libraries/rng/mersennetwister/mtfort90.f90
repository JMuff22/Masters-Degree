! $Id: mtfort90.f90 180 2010-07-29 10:34:55Z aakurone $

!-----------------------------------------------------------------!
!                                                                 !
!                                                                 !
! Module 'mtmod' for Mersenne twister random numbers.             !
!                                                                 !
! Public functions and subroutines:                               !
!                                                                 !
! sgrnd(seed)     initialize RNG (subroutine)                     !
! grnd()          double RN [0,1[ (double precision function)     !
! gaussrnd()      Gaussian RN (mean=0, std=1) (double precision   !
!                 function)                                       !
! igrnd(l,h)      integer RN in [l,h] (limits included)           !
!                 (integer function)                              !
!                                                                 !
! mtsave(f,forma) save RNG state                                  !
! mtget(f,forma)  restore RNG state                               !
!                 (overloaded subroutines)                        !
!                 f=string  : save/restore to/from file           !
!                 f=integer : save/restore to/from Fortran unit   !
!                 forma='U' or 'u' : read/write unformatted,      !
!                 else formatted                                  !
!                                                                 !
! Usage example:                                                  !
!                                                                 !
!    use defs, only : rk                                          !
!       ! or alternatively (see the definitions in the            !
!       ! beginning of the module)                                !
!       ! integer,parameter :: rk=selected_real_kind(10,40)       !
!                                                                 !
!    ...                                                          !
!                                                                 !
!    integer :: seed,i                                            !
!    real(rk) :: x,g                                              !
!                                                                 !
!    ...                                                          !
!                                                                 !
!    call sgrnd(seed)                                             !
!    x=grnd()                                                     !
!    g=gaussrnd()                                                 !
!    i=igrnd(0,100)                                               !
!    ...                                                          !
!                                                                 !
!-----------------------------------------------------------------!
!                                                                 !
! Obtained from                                                   !
! http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/VERSIONS/FORTRAN/mtfort90.f
!                                                                 !
! Changed real(8) to use selected_real_kind in module defs        !
! (file defs.f90, or defined locally as a constant, see below)    !
! and added 'implicit none' to all routines.                      !
!                                                                 !
!   A.Kuronen, April 2007                                         !
!                                                                 !
! Added igrnd(): integer random number function. A.Kuronen, 2009  !
! Added gaussrnd(): Gaussian random number. A.Kuronen, 2010       !
! Set most module variables private. A.Kuronen, 2010              !
!                                                                 !
!-----------------------------------------------------------------!
!
! Fortran translation by Hiroshi Takano.  Jan. 13, 1999.
!
!   genrand()      -> double precision function grnd()
!   sgenrand(seed) -> subroutine sgrnd(seed)
!                     integer seed
!
! This program uses the following non-standard intrinsics.
!   ishft(i,n): If n>0, shifts bits in i by n positions to left.
!               If n<0, shifts bits in i by n positions to right.
!   iand (i,j): Performs logical AND on corresponding bits of i and j.
!   ior  (i,j): Performs inclusive OR on corresponding bits of i and j.
!   ieor (i,j): Performs exclusive OR on corresponding bits of i and j.
!
!----------------------------------------------------------------------------
!
! Fortran version rewritten as an F90 module and mt state saving and getting
! subroutines added by Richard Woloshyn. (rwww@triumf.ca). June 30, 1999
!
!----------------------------------------------------------------------------
!
! A C-program for MT19937: Real number version
!   genrand() generates one pseudorandom real number (double)
! which is uniformly distributed on [0,1]-interval, for each
! call. sgenrand(seed) set initial values to the working area
! of 624 words. Before genrand(), sgenrand(seed) must be
! called once. (seed is any 32-bit integer except for 0).
! Integer generator is obtained by modifying two lines.
!   Coded by Takuji Nishimura, considering the suggestions by
! Topher Cooper and Marc Rieffel in July-Aug. 1997.
!
! This library is free software; you can redistribute it and/or
! modify it under the terms of the GNU Library General Public
! License as published by the Free Software Foundation; either
! version 2 of the License, or (at your option) any later
! version.
! This library is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
! See the GNU Library General Public License for more details.
! You should have received a copy of the GNU Library General
! Public License along with this library; if not, write to the
! Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
! 02111-1307  USA
!
! Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.
! When you use this, send an email to: matumoto@math.keio.ac.jp
! with an appropriate reference to your work.
!
!----------------------------------------------------------------------------

module mtmod
  use defs, only : rk
  implicit none
  ! If you don't want to use an external module to define the real type (rk)
  ! just comment the 'use' startement above and uncomment the parameter definition below.
  !integer,parameter :: rk=selected_real_kind(10,40) ! This is double precision
  
  integer,parameter,private :: defaultsd = 4357    ! Default seed  
  integer,parameter,private :: N = 624, N1 = N + 1 ! Period parameters
  integer,save,dimension(0:N-1),private :: mt      ! Array for the state vector
  integer,save,private :: mti = N1
  
  ! Overload procedures for saving and getting mt state
  interface mtsave
     module procedure mtsavef
     module procedure mtsaveu
  end interface
  interface mtget
     module procedure mtgetf
     module procedure mtgetu
  end interface
  
contains

  
  !---------------------------------------------------------------!
  !                                                               !
  ! Initialization subroutine                                     !
  !                                                               !
  !---------------------------------------------------------------!

  subroutine sgrnd(seed)
    implicit none
    ! Setting initial seeds to mt[N] using the generator Line 25 of Table 1 in
    ! [KNUTH 1981, The Art of Computer Programming Vol. 2 (2nd Ed.), pp102]
    integer, intent(in) :: seed    
    mt(0) = iand(seed,-1)
    do mti=1,N-1
       mt(mti) = iand(69069 * mt(mti-1),-1)
    enddo
    return
  end subroutine sgrnd
  

  !---------------------------------------------------------------!
  !                                                               !
  ! Random number generator: [0,1[                                !
  !                                                               !
  !---------------------------------------------------------------!

  function grnd()
    implicit none
    real(rk) :: grnd    
    ! Period parameters
    integer, parameter :: M = 397, MATA  = -1727483681 ! constant vector a
    integer, parameter :: LMASK =  2147483647          ! least significant r bits
    integer, parameter :: UMASK = -LMASK - 1           ! most significant w-r bits
    ! Tempering parameters
    integer, parameter :: TMASKB= -1658038656, TMASKC= -272236544    
    integer,save :: mag01(0:1)=[0,MATA] ! mag01(x) = x * MATA for x=0,1

    integer :: kk,y

    if (mti>=N) then               ! generate N words at one time
       if (mti==N+1) then          ! if sgrnd() has not been called,
          call sgrnd( defaultsd ) ! a default initial seed is used
       endif
       do kk=0,N-M-1
          y=ior(iand(mt(kk),UMASK),iand(mt(kk+1),LMASK))
          mt(kk)=ieor(ieor(mt(kk+M),ishft(y,-1)),mag01(iand(y,1)))
       enddo
       do kk=N-M,N-2
          y=ior(iand(mt(kk),UMASK),iand(mt(kk+1),LMASK))
          mt(kk)=ieor(ieor(mt(kk+(M-N)),ishft(y,-1)),mag01(iand(y,1)))
       enddo
       y=ior(iand(mt(N-1),UMASK),iand(mt(0),LMASK))
       mt(N-1)=ieor(ieor(mt(M-1),ishft(y,-1)),mag01(iand(y,1)))
       mti = 0
    endif
    
    y=mt(mti)
    mti = mti + 1 
    y=ieor(y,TSHFTU(y))
    y=ieor(y,iand(TSHFTS(y),TMASKB))
    y=ieor(y,iand(TSHFTT(y),TMASKC))
    y=ieor(y,TSHFTL(y))
    
    if (y<0) then
       grnd=(dble(y)+2.0d0**32)/(2.0d0**32-1.0d0)
    else
       grnd=dble(y)/(2.0d0**32-1.0d0)
    endif
    
    return

  contains

    integer function TSHFTU(y)
      integer,intent(in) :: y
      TSHFTU=ishft(y,-11)
      return
    end function TSHFTU
    integer function TSHFTS(y)
      integer,intent(in) :: y
      TSHFTS=ishft(y,7)
      return
    end function TSHFTS
    integer function TSHFTT(y)
      integer,intent(in) :: y
      TSHFTT=ishft(y,15)
      return
    end function TSHFTT
    integer function TSHFTL(y)
      integer,intent(in) :: y
      TSHFTL=ishft(y,-18)
      return
    end function TSHFTL

  end function grnd
  

  !---------------------------------------------------------------!
  !                                                               !
  ! Integer random number generator:                              !
  ! return a random integer between in [l,h]                      !
  ! (boundaries l and h included)                                 !
  !                                                               !
  ! A.Kuronen, 2009                                               !
  !                                                               !
  !---------------------------------------------------------------!

  integer function igrnd(l,h)
    implicit none
    integer,intent(in) :: l,h
    real(rk) :: u,r
    u=grnd()
    r=(h-l+1)*u+l
    igrnd=int(r)
    return
  end function igrnd


  !---------------------------------------------------------------!
  !                                                               !
  ! Random numbers with normal (Gaussian) distribution.           !
  ! Mean is 0 and standard deviation is 1                         !
  ! See W.H.Press et al., Numerical Recipes 1st ed., page 203     !
  !                                                               !
  ! A.Kuronen, 2009                                               !
  !                                                               !
  !---------------------------------------------------------------!
  
  
  function gaussrnd()
    implicit none
    real(rk) :: gaussrnd
    real(rk) :: fac,v1,v2,r
    real(rk), save :: gset
    integer, save :: iset=0

    if (iset==0) then ! Create a new RN
       r=100.0
       do while (r>1.0)
          v1 = 2.0*grnd()-1.0
          v2 = 2.0*grnd()-1.0
          r = v1*v1+v2*v2
       end do
       fac = sqrt(-2.0*log(r)/r)
       gset = v1*fac
       gaussrnd = v2*fac
       iset = 1
    else ! Use the 2nd NR from the previous call
       gaussrnd = gset
       iset = 0
    endif
    return
  end function gaussrnd
  
  

  !---------------------------------------------------------------!
  !                                                               !
  ! State saving subroutines.                                     !
  !                                                               !
  !  Usage:  call mtsave( file_name, format_character )           !
  !     or   call mtsave( unit_number, format_character )         !
  !  where   format_character = 'u' or 'U' will save in           !
  !          unformatted form, otherwise state information will   !
  !          be written in formatted form.                        !
  !                                                               !
  !---------------------------------------------------------------!

  subroutine mtsavef( fname, forma )
    implicit none
    
    !NOTE: This subroutine APPENDS to the end of the file "fname".
    
    character(*), intent(in) :: fname
    character, intent(in)    :: forma
    
    select case (forma)
    case('u','U')
       open(unit=10,file=trim(fname),status='UNKNOWN',form='UNFORMATTED',position='APPEND')
       write(10) mti
       write(10) mt       
    case default
       open(unit=10,file=trim(fname),status='UNKNOWN',form='FORMATTED',position='APPEND')
       write(10,*) mti
       write(10,*) mt       
    end select

    close(10)    
    return
  end subroutine mtsavef
  
  !---------------------------------------------------------------!

  subroutine mtsaveu(unum,forma)
    implicit none
    integer, intent(in)    :: unum
    character, intent(in)  :: forma
    
    select case (forma)
    case('u','U')
       write(unum) mti
       write(unum) mt       
    case default
       write(unum,*) mti
       write(unum,*) mt       
    end select
    
    return
  end subroutine mtsaveu
  

  !---------------------------------------------------------------!
  !                                                               !
  ! State getting subroutines.                                    !
  !                                                               !
  !  Usage:  call mtget( file_name, format_character )            !
  !     or   call mtget( unit_number, format_character )          !
  !  where   format_character = 'u' or 'U' will read in           !
  !          unformatted form, otherwise state information will   !
  !          be read in formatted form.                           !
  !                                                               !
  !---------------------------------------------------------------!

  subroutine mtgetf(fname,forma)
    implicit none
    character(*), intent(in) :: fname
    character, intent(in)    :: forma
    
    select case (forma)
    case('u','U')
       open(unit=10,file=trim(fname),status='OLD',form='UNFORMATTED')
       read(10) mti
       read(10) mt
    case default
       open(unit=10,file=trim(fname),status='OLD',form='FORMATTED')
       read(10,*) mti
       read(10,*) mt
    end select

    close(10)
    return
  end subroutine mtgetf
  
  !---------------------------------------------------------------!

  subroutine mtgetu(unum,forma)
    implicit none
    integer, intent(in)    :: unum
    character, intent(in)  :: forma
    
    select case (forma)
    case('u','U')
       read(unum) mti
       read(unum) mt
    case default
       read(unum,*) mti
       read(unum,*) mt
    end select
    
    return
  end subroutine mtgetu  

end module mtmod

