//(string-append "Hello\n" "world!")
"Hello\n"+"world!";
//(* (+ 1 2 3) 7)
(1+2+3)*7;
//(< 41 (* 6 7))
41<(6*7);
//(equal? (* (+ 1 2 3) 7) 42)
42 == ((1+2+3)*7);
//(equal? "Spongebob" "Squarepants")
"Spongebob" == "Squarepants";
//(and (equal? (* 6 7) 42) (equal? "Spongebob" "Squarepants"))
42 == (6*7) && "Spongebob" == "Squarepants";
//(equal? 42 (if (< 3 5) (* 6 7) "turnip"))
42 == (3 < 5 ? (6*7) :"turnip");
// (or #t (/ 1 0))
true || (1/0);
// (and #f (/ 1 0))
false && (1/0);