
function lcg(seed)
  implicit none
  integer,parameter :: ik=selected_int_kind(15),&
                     & rk=selected_real_kind(10,40)
  real(rk) :: lcg
  integer(ik),intent(inout) :: seed
  integer(ik),save :: a=69069,c=1,m=4294967296
  real(rk),save :: rm=4294967296.0

  seed= mod(seed*a+c,m)
  lcg=seed/rm

end function lcg
  
