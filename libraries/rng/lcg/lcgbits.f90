program lcgmain
  implicit none
  integer,parameter :: ik=selected_int_kind(15),&
                     & rk=selected_real_kind(10,40)
  integer :: i,imax,iargc,j,k
  integer(ik) :: seed
  character(len=80) :: argu
  integer(ik) :: lcg,x,y,z
  integer :: getseed
  character(len=300) :: c,s

  call getarg(1,argu); read(argu,*) imax
  call getarg(2,argu); read(argu,*) seed
  if (seed<=0) seed=getseed()
  write(0,'(a,i10)') 'Seed ',seed

  do i=1,imax
     x=lcg(seed)
     y=lcg(seed)
     z=lcg(seed)
     write(c,'(3b32.32)') x,y,z
     s=''
     do j=1,len_trim(c),2
        k=(j+1)/2
        if (c(j:j+1)=='00') s(k:k)=' '
        if (c(j:j+1)=='01') s(k:k)=' '
        if (c(j:j+1)=='10') s(k:k)=' '
        if (c(j:j+1)=='11') s(k:k)='X'
     end do
     write(6,'(a)') trim(s)
  end do

end program lcgmain

function lcg(seed)
  implicit none
  integer,parameter :: ik=selected_int_kind(15),&
                     & rk=selected_real_kind(10,40)
  integer(ik) :: lcg
  integer(ik),intent(inout) :: seed
  integer(ik),save :: a=69069,c=1,m=4294967296

  seed= mod(seed*a+c,m)
  lcg=seed

end function lcg
  
