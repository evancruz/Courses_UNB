(module hello racket
  ;provide nameOfFunction
  (provide hello)
  (define (hello)
    (displayln "Hello world!"))
  
  (require rackunit)
  (check-equal? (with-output-to-string hello) "Hello world!\n"))

(module+ main
  (hello))
