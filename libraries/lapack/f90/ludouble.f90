
program ludouble

! LU decomposition of a square matrix using LAPACK
  implicit none

  integer,parameter :: rk=8
  real(rk),allocatable :: a(:,:),a0(:,:),p(:,:),l(:,:),u(:,:),tmp(:)
  integer :: n,i,j,ok
  integer,allocatable :: pivot(:)

  read(5,*) n
  allocate(a(n,n),a0(n,n),p(n,n),l(n,n),u(n,n),tmp(n),pivot(n))
  do i=1,n
     read(5,*) (a(i,j),j=1,n)
  enddo
  a0=a


  write(6,'(/a)') 'Before'
  write(6,'(/a)') 'A'
  do i=1,n
     write(6,'(20g16.8)') (a(i,j),j=1,n)
  enddo

  call dgetrf(n, n, a, n, pivot, ok)

  write(0,'(/a,i3)') 'ok: ',ok
  write(0,'(a,20i3)') 'pivot: ',pivot

  l=0.0
  u=0.0
  p=0.0
  forall (i=1:n,j=1:n,i==j) 
     l(i,j)=1.0
     p(i,j)=1.0
  end forall
  forall (i=1:n,j=1:n,i>j ) l(i,j)=a(i,j)
  forall (i=1:n,j=1:n,i<=j) u(i,j)=a(i,j)
  do i=n,1,-1
     if (i/=pivot(i)) then
        tmp=p(i,1:n)
        p(i,1:n)=p(pivot(i),1:n)
        p(pivot(i),1:n)=tmp
     end if
  end do

  
  write(6,'(/a)') 'P'
  do i=1,n
     write(6,'(20g16.8)') (p(i,j),j=1,n)
  enddo
  write(6,'(/a)') 'L'
  do i=1,n
     write(6,'(20g16.8)') (l(i,j),j=1,n)
  enddo
  write(6,'(/a)') 'U'
  do i=1,n
     write(6,'(20g16.8)') (u(i,j),j=1,n)
  enddo

  write(6,'(/a)') 'Check'
  a=matmul(p,matmul(l,u))
  write(6,'(/a)') 'A'
  do i=1,n
     write(6,'(20g16.8)') (a(i,j),j=1,n)
  enddo



end program ludouble

