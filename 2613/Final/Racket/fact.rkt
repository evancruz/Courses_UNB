#lang racket

(define (sixes-and-sevens lst)
  (define (helper lst lst2)
    (cond
      [(empty? lst)  (reverse lst2)]
      [(= (remainder (first lst) 6) 0) (helper (rest lst) (cons (first lst) lst2))]
      [(= (remainder (first lst) 7) 0) (helper (rest lst) (cons (first lst) lst2))]
      [else (helper (rest lst) lst2)]))
  (helper lst empty))

(module+ test
  (require rackunit)
  (check-equal? (sixes-and-sevens '(1 6 7 12)) '(6 7 12)))