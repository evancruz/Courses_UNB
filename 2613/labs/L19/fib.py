#!/usr/bin/python3
class Fib:
    def __init__(self,max):
        self.max = max
        self.a = 0
        self.b = 1

    def __iter__(self):
        self.a = 0
        self.b = 1
        return self


    def __next__(self):
        if self.a < self.max:
            tmp = self.a
            self.a, self.b = self.b, self.a + self.b
            return tmp


        else:
            raise StopIteration

# 21. Deep Work by Cal Newport
# 29. How to Win at the Sport of Business: If I Can Do It, You Can Do It by Mark Cuban
# 41. The Art of Thinking Clearly by Rolf Dobelli
# 42. The Hard Thing About Hard Things by Ben Horowitz
# Atomic Habits: An Easy & Proven Way to Build Good Habits & Break Bad Ones
# Advanced Calculus by Woods

#  “The chief enemy of good decisions is a lack of sufficient perspectives on a problem.”


# Strength
# Starting Strength: Basic Barbell Training