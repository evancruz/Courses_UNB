a = [4;4];
beta = 7.5;

range = [-4:0.1:8];
[X Y] = meshgrid(range,range);
tic();
Z=arraydelta(beta,a,X,Y);
toc()

surf(X,Y,Z);