#lang slideshow
(require math/number-theory)

;; if not trivially divisible then return f so it will be removed. Otherwise return t}
(define (!trivialDivisible num divisor)
  (cond
    [(= num divisor) #t]
    [(zero? (remainder num divisor)) #f]
    [else #t]))


(define (drop-divisible divisor lst)
  (cond
    [(= (length lst) 1) lst]
    [else (filter (lambda (i) (!trivialDivisible i divisor))lst)]))


(define (sieve-with divisorLst lst)
  (cond
    [(= (length divisorLst) 1) (drop-divisible (first divisorLst) lst)]
    [else (sieve-with (rest divisorLst) (drop-divisible (first divisorLst) lst)) ]))

(define (sieve n)
  (define nums (range 2 (add1 n)))
  (sieve-with nums nums))

;; Part 4, use prime? function from math module and use it as a test to check against my solution
(define (getPrime n)
  (define nums (range 0 (add1 n)))
  (filter (lambda (i) (prime? i)) nums))

;; Dr. David Bremner said we did not have to check for an empty list, or when a divisor is either 0 or 1
(module+ test
  (require rackunit)
  (check-equal? (drop-divisible 3 (list 2 3 4 5 6 7 8 9 10)) (list 2 3 4 5 7 8 10))
  (check-equal? (drop-divisible 8 (list 8)) (list 8))
  (check-equal? (drop-divisible 3 empty) empty)
  (check-equal? (sieve-with '(2 3) (list 2 3 4 5 6 7 8 9 10)) (list 2 3 5 7))
  (check-equal? (sieve-with '(5 7) (list 2 3 4 5 6 7 8 9 10 12 14 15 16 21 22)) (list 2 3 4 5 6 7 8 9 12 16 22))
  (check-equal? (sieve-with '(5 7) (list 10 15 20 22)) (list 22))
  (check-equal? (sieve 10) (list 2 3 5 7))
  (check-equal? (sieve 10) (list 2 3 5 7))
  (check-equal? (getPrime 200) (sieve 200)))


;; Uncomment to run this test. It takes a little bit
#|{ (module+ longTest
  (require rackunit)
  (check-equal? (getPrime 100000) (sieve 100000))) }
|#