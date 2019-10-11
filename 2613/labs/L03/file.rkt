#lang racket

(define (my-+ a b)
  (if (zero? a)
      b
  (my-+ (sub1 a) (add1 b))))

(define (my-* a b)
       (cond
       [(zero? a) 0]
       [(= a 2) (my-+ b b)]
       [(= a 1) b]
       [else (my-+ b (my-* (sub1 a) b))]))

(provide my-+
         my-*)


(module+ test
  (require rackunit)
  (check-equal? (my-+ 1 1) 2 "Simple Addition")
  (check-equal? (my-* 1 2) 2 "Simple Mul")
  (check-equal? (my-* 0 2) 0 "Mul 0")
  (check-equal? (my-* 3 125) 375 "Mul Complex"))