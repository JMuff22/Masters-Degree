
% Plot the the GSL rott finding function

clf;

a=1.0;
b=10.0;
c=0.1;
nc=10;
v1=[-1 -0.5 0 0.5 1];
v2=[-10 -5 0 5 10];
v3=[-500 -200 -100 -50 -20 -2 0 2 20 50 100 200 500];

[X,Y]=meshgrid(-2:0.1:4 , -2:0.1:4);
Z1=a*(1-X-c*Y.*Y);
Z2=b*(Y-X.*X);
Z3=Z1.*Z1+Z2.*Z2;

load gsl_multidim_root.traj;
plot(gsl_multidim_root(:,1),gsl_multidim_root(:,2),'-+b');
hold on

[c1,h1]=contour(X,Y,Z1,v1);clabel(c1,h1);
[c2,h2]=contour(X,Y,Z2,v2);clabel(c2,h2);
%[c3,h3]=contour(X,Y,Z3,v3);clabel(c3,h3);




