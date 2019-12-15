def powergen(n):
   res = 1
   yield res
   while(True):
      res = res * n
      yield res

def test_powergen():
    gen = powergen(2)
    first = next(gen)
    second = next(gen)
    third = next(gen)
    assert (first == 1)
    assert (second == 2)
    assert (third == 4)


def test_powergen_list():
    gen = powergen(3)
    threes = [next(gen) for i in range(9)]
    assert(threes == [1, 3, 9, 27, 81, 243, 729, 2187, 6561])


class FizzBuzz:
   def __init__(self, max=100):
      self.n = 1
      self.max = max

   def __iter__(self):
      self.n = 1
      return self

   def __next__(self):
      if self.n > self.max:
         raise StopIteration
      else:
         #  do fizz buzz
         if self.n % 3 == 0 and self.n % 5 == 0:
            self.n += 1
            return 'FizzBuzz'
         elif self.n % 3 == 0:
            self.n += 1
            return 'Fizz'
         elif self.n % 5 == 0:
            self.n += 1
            return 'Buzz'
         else:
            num = self.n
            self.n += 1
            return num

def test_fizzbuzz_next():
    fb = FizzBuzz(15)
    assert (list(fb) == [1, 2, 'Fizz', 4, 'Buzz', 'Fizz', 7, 8, 'Fizz',
                         'Buzz', 11, 'Fizz', 13, 14, 'FizzBuzz'])


def test_fizzbuzz_iter():
    fb = FizzBuzz(100)
    first = list(fb)
    second = list(fb)
    assert (first == second)


if __name__ == '__main__':
   test_powergen()
   test_powergen_list()
   test_fizzbuzz_next()
   test_fizzbuzz_iter()
   fb = FizzBuzz(15)

