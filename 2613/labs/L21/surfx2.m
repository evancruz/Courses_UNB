a = [4;4];
    beta = 7.5;
    range = [-4:0.1:8];
    [X Y] = meshgrid(range,range);
    
    %wrapped in an anonymous function that takes two scalars
    tic();
    f=@(x,y)(delta(beta, a,[x;y])); 
    Z=arrayfun(f,X,Y);
    toc()
    surf(X,Y,Z);
