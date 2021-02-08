
program eigendouble

! Eigenvalues of a square matrix using LAPACK
  implicit none

  
  integer,parameter :: rk=selected_real_kind(10,40)
  real(rk),allocatable :: a0(:,:)
  integer :: n,i,j,ok
  complex(rk),allocatable :: a(:,:),w(:),work(:)
  complex(rk) :: dummy(1,1)

  read(5,*) n
  allocate(a(n,n),a0(n,n),w(n),work(2*n))
  do i=1,n
     read(5,*) (a0(i,j),j=1,n)
  enddo

  a=a0
  call zgeev('N','N',n,a,n,w,dummy,1,dummy,1,work,2*n,work,ok)
  write(6,'(/,a)') 'Eigenvalues of A:'
  write(6,'(2g16.8)') (w(i),i=1,n)

  a=a0
  a=matmul(transpose(a),a)
  call zgeev('N','N',n,a,n,w,dummy,1,dummy,1,work,2*n,work,ok)
  write(6,'(/,a)') 'Eigenvalues of A^T*A:'
  write(6,'(2g16.8)') (w(i),i=1,n)



end program eigendouble

