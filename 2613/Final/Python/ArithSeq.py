'''Write a python iterator class ArithSeq where ArithSeq(first, step, max) creates a sequence of integers starting at first, going up by step, and stopping at the last value in the sequence no larger than max. Your class should pass the following tests.'''

class ArithSeq:

   def __init__(self, first, step, max):
      self.first = first
      self.step = step
      self.max = max

   def __iter__(self):
      return self

   def __next__(self):
      if self.first > self.max:
         raise StopIteration
      num = self.first
      self.first += self.step 
      return num
   


def test_evens():
    assert [x for x in ArithSeq(0, 2, 10)] == [0, 2, 4, 6, 8, 10]


def test_odds():
    assert [x for x in ArithSeq(1, 2, 10)] == [1, 3, 5, 7, 9]
    

def test_evens2():
    assert arithSeq2(0, 2, 10) == [0, 2, 4, 6, 8, 10]

def arithSeq2(first, step, max):
   return [item for item in range(first, max+1, step)]

test_evens2()



