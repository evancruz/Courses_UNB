#lang racket

(require (for-syntax racket/match))
(require (for-syntax "let-transformer.rkt"))

(define-syntax (Let* stx)
  (datum->syntax #'here
                 (let-transformer (syntax->datum stx))))
