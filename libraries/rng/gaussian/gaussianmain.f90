program gaussianmain

  implicit none
  integer,parameter :: rk=selected_real_kind(10,40) ! Double precision
  real(rk) :: gaussianrand
  integer :: i,seed=13579

  do i=1,10000
     write(6,*) gaussianrand(seed),gaussianrand(seed)
  end do
  stop
end program gaussianmain


  
