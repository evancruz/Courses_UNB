#lang racket

(require xml)
(define (load-xexpr path)
  (xml->xexpr (document-element (read-xml (open-input-file path)))))

(require explorer)
(define (load-rubrics path)
  (rest (rest (load-xexpr path))))



(module+ test
  (require rackunit)
  (define rubrics (load-rubrics  "rubrics.xml"))
  (check-equal? (length rubrics) 5)
  (for ([elt rubrics])
    (check-equal? (first elt) 'rubric)))

;;;;;;;;;;
;;Part 2
;;;;;;;;;;


(define (assoc* key listIn)
  (cond
    [(empty? listIn) #f]
    [(and (pair? (first listIn)) (equal? key (first(first listIn)))) (second (first listIn))]
    [else (assoc* key (rest listIn))]))


(module+ test
  (define test-list '(1 [keep 2] 3 [keep 4] [keep 5] 6))
  (check-equal? (assoc* 'keep test-list) 2)
  (check-equal? (assoc* 'discard test-list) #f))

(define (rubric-name rubric)
  (assoc* 'name (second rubric)))

(module+ test
  (check-equal?
   (sort (map rubric-name rubrics) string<=?)
   '("JavaScript Assignment" "Journal Entry" "Octave Assignment" "Python Assignment"
                             "Racket assignment")))

;;;;;;;;;;
;;Part 3
;;;;;;;;;;

(define (equalkey? key lst)
  (if (equal? key (first lst)) #t #f))

(define (assoc-all key listIn)
  (define refinedList (filter pair? listIn))
  (filter (curry equalkey? key) refinedList))


(module+ test
  (define test-list2 '(1 [keep 2] 3 [discard 4] [keep 5] 6))
  (check-equal? (assoc-all 'keep test-list) '([keep 2] [keep 4] [keep 5]))
  (check-equal? (assoc-all 'keep test-list2) '([keep 2] [keep 5])))

;;;;;;;;;;
;;Part 4
;;;;;;;;;;


(define (criteria-groups listIn)
  (assoc-all `criteria_group (fourth listIn)))

(module+ test
  ;; Journals have one group, others have 2
  (check-equal? (sort (map length (map criteria-groups rubrics)) <=)
                '(1 2 2 2 2))
  (check-equal?
   (first ;; tag
    (first ;; first criteria group
     (criteria-groups (first rubrics))))
   'criteria_group))

;;;;;;;;;;
;;Part 5
;;;;;;;;;;

(define (criteria-levels listIn)
  (assoc-all `level (third (third listIn))))

(define (criteria-names listIn)
  (list (assoc* `name (second (third (fourth listIn)))) (assoc* `name (second (fourth (fourth listIn))))))


                                                     
(module+ test
  (for ([level  (criteria-levels (first (criteria-groups (first rubrics))))])
    (check-equal? (first level) 'level))
  (check-equal? (sort (criteria-names (first (criteria-groups (first rubrics)))) string<=?)
                '("Content" "Technical skills")))


;;;;;;;;;;;;;;;
;;;;Part 6
;;;;;;;;;;;;;;;

;;I dont know of a better way other than just drilling into the xml by calling fourth, third, etc
(define (level-name-score listIn)
 (list (assoc* `name (second listIn)) (exact-round(string->number(assoc* `level_value (second listIn))))))

  
(module+ test
  (check-equal? (map level-name-score (criteria-levels (first (criteria-groups (first rubrics)))))
                '(("Needs improvement" 0)
                  ("Minimally satifactory" 1)
                  ("Good" 2)
                  ("Excellent" 3))))



