
program qrdouble

! QR factorization of a square matrix using LAPACK DGEQRF. The matrix
! Q is computed from output of DGEQRF by routine DORGQR. Triangular
! matrix R is obtained as Q^T * A.

  implicit none
  
  integer,parameter :: rk=selected_real_kind(10,40)
  integer :: n,i,j,k,ok,lda,lwork,iar,iter
  real(rk),allocatable :: a(:,:),a0(:,:),a1(:,:),q(:,:),r(:,:),qq(:,:)
  real(rk),allocatable :: work(:),tau(:)
  logical :: symmetric,uppertriangular,printiter
  character(len=200) :: arg,form

  symmetric=.false.
  uppertriangular=.false.
  form='(100g14.4)'

  iar=command_argument_count()
  if (iar/=1.and.iar/=2) then
     call get_command_argument(0,arg)
     write(0,'(a,a,a)') 'usage : ',trim(arg),' iter [g/s/u]'
     write(0,'(a)') 'g=general, s=symmetric, u=upper triangular'
     stop
  end if
  call get_command_argument(1,arg); read(arg,*) iter
  if (iter<0) then
     iter=-iter
     printiter=.true.
  else
     printiter=.false.
  end if
  if (iar==2) then
     call get_command_argument(2,arg)
     symmetric=arg(1:1)=='s'
     uppertriangular=arg(1:1)=='u'
  end if

  read(5,*) n
  lwork=8*n
  lda=n
  allocate(a(n,n),a0(n,n),a1(n,n),q(n,n),r(n,n),qq(n,n))
  allocate(work(lwork),tau(n))
  do i=1,n
     read(5,*) (a(i,j),j=1,n)
  enddo

  if (symmetric) a=(a+transpose(a))/2.0
  if (uppertriangular) forall (i=1:n,j=1:n,i>j) a(i,j)=0.0

  a0=a

  write(6,'(/a)') 'Original A :'
  do i=1,n
     write(6,form) a(i,1:n)
  enddo

  iterloop: do k=1,iter

     call dgeqrf(n,n,a,n,tau,work,lwork,ok)
     if (ok/=0) then
        write(0,'(a,i0)') 'ok : ',ok
        stop
     end if
     call dorgqr(n,n,n,a,n,tau,work,lwork,ok)
     q=a
     r=matmul(transpose(q),a0)
     a=matmul(r,q)
     a0=a
     qq=matmul(transpose(q),q)
     
     if (k==iter.or.printiter) then
        write(6,'(/,a)') 'Output A :'
        do i=1,n
           write(6,form) a(i,1:n)
        end do
        write(6,'(/,a)') 'Output Q :'
        do i=1,n
           write(6,form) q(i,1:n)
        end do
        write(6,'(/,a)') 'Output R :'
        do i=1,n
           write(6,form) r(i,1:n)
        end do
        write(6,'(/,a)') 'Check Q^T * Q :'
        do i=1,n
           write(6,form) qq(i,1:n)
        end do
        if (k==1) then
           write(6,'(/,a)') 'Check Q*R :'
           a1=matmul(q,r)
           do i=1,n
              write(6,form) a1(i,1:n)
           end do
        end if
        write(6,'(/)')
     end if

  end do iterloop

end program qrdouble

