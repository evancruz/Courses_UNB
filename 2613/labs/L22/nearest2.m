function out = nearest2(v, k, data)
  %data(1:end,2:end)
  diff = data(:,2,end) - ones(rows(data),1)*v(2:end);
  % -  a column of 1's as tall as data is
  %2 matrices that are the same shape. taking the difference between each test vector and training vector
  %now calculate all the vectornorms
  %we just need square of the norm. 
  %a <b if and only if a^2 < b^2
  normsq = dot(diff,diff,2)
  %dot product is usually about vectors. 
  [sorted, indices]=sort(normsq);
  out = sort(transpose(indices(1:k)));
endfunction


%diff explaination
% >> diff = data(:,2:end) - ones(4,1) * [1,2]
%diff =
%
%  -1  -2
%  -1  -1
%   0  -2
%   0  -1



%!test
%! v = [0,1,1];
%! data = [0,0,0; 0,0,1; 0,1,0; 1,1,1];
%! assert(nearest2(v,1,data) == 4)
%! assert(nearest2(v,3,data) == [2,3,4])