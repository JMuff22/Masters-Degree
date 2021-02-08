function myrand(seed)
  implicit none
  
  ! ---------------------------
  ! Random number generator
  ! uniform distribution [0,1[
  ! ---------------------------
  
  integer,parameter :: rk=selected_real_kind(10,50)
  real(rk) :: myrand
  integer,intent(inout) :: seed  
  integer,parameter :: a=16807, m=2147483647, q=127773, r=2836
  real(rk),parameter ::  minv=1d0/m

  seed = a*mod(seed, q) - r*(seed/q)  
  if (seed<= 0) seed = seed+m  
  myrand = seed*minv 
  

end function myrand
