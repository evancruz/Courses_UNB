function timeit(reps, func,varargin)
    times = zeros(reps, 1);

    for i=1:reps
      tic(); func(varargin{:}); times(i) = toc();
    end

    times = sort(times);
    fprintf ('%s\tmedian=%.3fms median=%.3fms total=%.3fms\n',func2str(func), median(times)*1000,
             mean(times)*1000, sum(times)*1000);
endfunction

%!test "nullary function"
%! timeit(10000,@rand)

%!test "unary function"
%! timeit(10000,@rand,1)

%!test "Binary function"
%! timeit(10000,@plus,1,2)

%!test "Ternery function"
%! timeit(10000,@plus,1,2,3)
