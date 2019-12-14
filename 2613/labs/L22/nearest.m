function out = nearest(v, k, data) %data is a matrix of data we are measuring distance to.
  for i=1:rows(data)
    dist(i)=norm(v(2:end) - data(i,2:end)); %calculates distance from v to row i
  endfor
  [sorted, indices]=sort(dist); %sorts the distances
  out = sort(indices(1:k)); 
  %return k results. used to break ties. give me the indices of the k smallest numbers. in test 3 k =1. 
  %
endfunction

%!test
%! v = [0,1,1]
%! data = [0,0,0; 0,0,1; 0,1,0; 1,1,1]
%! assert(nearest(v,1,data) == 4)

%! assert(nearest(v,3,data) == [2,3,4])