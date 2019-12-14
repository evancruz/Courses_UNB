a = [4;4];
beta = 7.5;

%% Generating vectors
range = [-4:0.1:8];
%range = [-8:-1.1:8];

% Compute cartesian product (grid)
[X,Y] = meshgrid(range,range);
[rows,cols] = size(X)


%z(i,j) == delta(beta, a [x[i,j]; y[i,j]]) -> plotting delta as a function of b 
tic();
for i = 1: rows
  for j = 1: cols
    b = [X(i,j); Y(i,j)]; %build me a column vector. two rows with one element. 
    Z(i,j) = delta(beta,a,b);
  endfor
endfor
toc()






surf(X,Y,Z);
%contourf(X,Y,Z);