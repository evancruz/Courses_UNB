function out=findclass(v, k, data, fun=@nearest)
    selection=fun(v,k,data)
    out = mode(data(selection,1));
    %find all the class neighbors
    %then call mode

endfunction

%!test
%! v = [0,1,1]; 

%! data = [0,0,0; 0,0,1; 0,1,0; 1,1,1];
%! assert(findclass(v,1,data) == 1)
%wrong answer
%! assert(findclass(v,3,data) == 0)
%right answer with 3 nearest neighbors. returning 2,3,4


 %indexing one array with another
 % data = [0,0,0; 0,0,1; 0,1,0; 1,1,1];
 % >> data([2,3,4],1)
%ans =
%
%  0
%  0
%  1