BEGIN {
  s=11;
  a=29;
  c=1;
  m=100; 
  n=1000;

  for (i=0;i<n;i++) {
    s=(a*s+c)%m;
    print s;
  }

}

