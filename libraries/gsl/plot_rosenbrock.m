
% Plot the the GSL rott finding function

a=1.0;
b=10.0;
c=0.1;
nc=10;
v1=[-1 -0.5 0 0.5 1];
v2=[-10 -5 0 5 10];

[X,Y]=meshgrid(-2:0.1:4 , -2:0.1:4);
Z1=a*(1-X-c*Y.*Y);
Z2=b*(Y-X.*X);
[c1,h1]=contour(X,Y,Z1,v1);
hold
[c2,h2]=contour(X,Y,Z2,v2);
%axis equal;
hold;
clabel(c1,h1);
clabel(c2,h2);

