function [a,b] = randomsplit(matrix1, splitNum)
  numRows = rows(matrix1);
  splitRow = floor(numRows * splitNum);
  splitRowRest = numRows - splitRow;

  shuffled = matrix1(randperm(numRows),:);
  a = shuffled(1: splitRow,:);
  b = shuffled(splitRow+1: numRows, :);

endfunction

%!assert(randomsplit(zeros(10,1), 0.5) == [zeros(5,1),zeros(5,1)])

%!test
%! [foo, bar] = randomsplit(zeros(10,1), 0.7);
%! assert(foo == zeros(7,1))
%! assert(bar == zeros(3,1))
%! x = reshape ([11, 21, 31, 41, 51, 61, 71, 81, 91, 101], 10, 1);
%! y = reshape ([11,21,31,42,51,61,71,81,91], 3, 3);
%! [a,b] = randomsplit(x, 0.5);
%! [c,d] = randomsplit(y, 0.5);
%! assert(size(a) == [5, 1])
%! assert(size(b) == [5, 1])
%! assert(size(c) == [1, 3])
%! assert(size(d) == [2, 3])