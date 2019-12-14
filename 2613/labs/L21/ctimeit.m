function ctimeit(func, argument, reps)
  
    start = cputime();
    for i = 1: reps
      func(argument);
    endfor
    
    used = cputime() - start;
    
    fprintf ( '%s\tmean = %.3fms total = %.3fms\n', func2str(func), used*1000 / reps, used*1000)
endfunction
