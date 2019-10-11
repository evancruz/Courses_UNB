#lang racket

(provide let-transformer)
(define (let-transformer lst)
  (match lst
    [(list 'Let* '() body) body]
    [(list 'Let* (cons (list id val) tail) body)
     (list 'let  (list (list id val))
           (let-transformer
            (list 'Let* tail body)))]))

(define test-expr '(Let* ([x 5]
                          [y (- x 3)])
                         (+ y y)))
(module+ test
  (require rackunit)
  (check-equal? (let-transformer test-expr)
                '(let ([x 5]) (let ([y (- x 3)]) (+ y y)))))