#lang slideshow

(define (fact n)
      (cond
        [(zero? n) 1]
        [else (* n (fact (sub1 n))) ]))

(module+ test
  (require rackunit)
  (check-equal? (fact 10) 3628800))

(define (list-length list)
  (if (empty? list)
      0
  (+ 1 (list-length list))))

(module+ test
  (require rackunit)
  (define test-list '(1 2 3))
  (check-equal? (length test-list) (list-length test-list)))
