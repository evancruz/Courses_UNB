#lang racket
#;(define (drop-divisible divisor lst)
  (define (helper i) (divisible? i divisor))
  (filter helper lst))