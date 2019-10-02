#lang racket

(require xml)
(define (load-xexpr path)
  (xml->xexpr (document-element (read-xml (open-input-file path)))))