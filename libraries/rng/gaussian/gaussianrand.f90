function uniformrand(seed)
  implicit none

  ! -----------------------------------------------------------
  ! Park-Miller "minimal" Random number generator
  ! uniform distribution ]0,1[ . See Numerical Recipes ch. 7.0
  ! -----------------------------------------------------------

  integer,parameter :: rk=selected_real_kind(10,40) ! Double precision
  real(rk) :: uniformrand
  integer :: seed,IA,IM,IQ,IR,MASK
  real(rk) :: AM
  integer :: k
  parameter (IA=16807,IM=2147483647,AM=1.0/IM,IQ=127773,IR=2836,MASK=123459876)
  
  seed=ieor(seed,MASK)
  k=seed/IQ
  seed=IA*(seed-k*IQ)-IR*k
  if (seed < 0) seed=seed+IM
  uniformrand=AM*seed
  seed=ieor(seed,MASK)
  return
end function uniformrand


function gaussianrand(seed)
  implicit none
  
  ! ---------------------------------------------------------
  ! Random numbers with normal (Gaussian) distribution.
  ! Mean is 0 and standard deviation is 1
  ! See W.H.Press et al., Numerical Recipes 1st ed., page 203
  ! ---------------------------------------------------------
  
  integer,parameter :: rk=selected_real_kind(10,40) ! Double precision
  real(rk) :: gaussianrand
  integer :: seed
  real(rk) :: fac,v1,v2,r
  real(rk), save :: gset
  integer, save :: iset=0
  real(rk) :: uniformrand
  
  if (iset==0) then
1    v1 = 2.*uniformrand(seed)-1.
     v2 = 2.*uniformrand(seed)-1.
     r = v1*v1+v2*v2
     if (r.ge.1.) goto 1
     fac = sqrt(-2.0*log(r)/r)
     gset = v1*fac
     gaussianrand = v2*fac
     iset = 1
  else
     gaussianrand = gset
     iset = 0
  endif

  return
end




