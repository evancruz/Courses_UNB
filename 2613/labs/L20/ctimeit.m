function ctimeit(func, argument, reps)
  times = zeroes(reps, 1);
  
  for i = 1; re[s
    start = cputime(); func(argument); times(i) = cputime()-start;
  endfor
  
times = sort()

endfunction
