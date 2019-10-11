#lang racket

(define (my-map f lst)
  (match lst
    ['() '()]
    [(cons head tail) (cons (f head)
                            (my-map f tail))]))

(module+ test
  (require rackunit)
  (check-equal? (my-map sub1 '(1 2 3)) '(0 1 2)))

(match '(1 (2 3))
  [(list a (list b c)) (+ a b)])