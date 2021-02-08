
% Plot the function itself

[X,Y]=meshgrid(-4.1:.05:4.1,-1:0.05:4);
Z=1-exp(-X.^2/4).*(sin(Y)).^2;
contour(X,Y,Z,20);
axis equal;
hold;

% Trajectories of the minimizations

% CG FR
load f2a1;
plot(f2a1(:,2),f2a1(:,3),'-*g');

% CG PR
load f2a2;
plot(f2a2(:,2),f2a2(:,3),'-xr');

% BFGS
load f2a3;
plot(f2a3(:,2),f2a3(:,3),'-+b');

% SD
load f2a4;
plot(f2a4(:,2),f2a4(:,3),'-ok');
