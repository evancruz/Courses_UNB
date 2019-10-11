#lang racket

(require "hello.rkt")

(hello)

(module+ test
(require rackunit)
(check-equal? (with-output-to-string hello) (begin (sleep 3) "Hello world!\n")))
