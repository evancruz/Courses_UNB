#lang racket

(define (sixes-and-sevens lst)
  (define (helper lst lst2)
    (cond
      [(empty? lst)  (reverse(flatten lst2))]
      [(zero? (modulo (first lst) 6)) (helper (rest lst) (list (list(first lst)) lst2))]
      [(zero? (modulo (first lst) 7)) (helper (rest lst) (list (list(first lst)) lst2))]
      [else (helper (rest lst) lst2)]))
  (helper lst empty))

(module+ test
  (require rackunit)
  (check-equal? (sixes-and-sevens '(1 6 7 12)) '(6 7 12)))