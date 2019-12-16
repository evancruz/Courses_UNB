#lang racket

(define (sixes-and-sevens lst)
  (cond
    [(empty? lst) lst]
    [else (reverse (helper lst empty))]
))

(define (helper lst acc)
  (if (empty? lst)
      (filter-not empty? acc)
  (helper (rest lst) (cons (dropND (first lst)) acc))))

(define (dropND element)
  (cond
    [(= (remainder element 6) 0) element]
    [(= (remainder element 7) 0) element]
    [empty]))


(module+ test
  (require rackunit)
  (check-equal? (sixes-and-sevens '(1 6 7 12)) '(6 7 12))) 
