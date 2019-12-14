def fib(max):
    a, b = 0, 1
    while a < max:
        yield a
        a, b = b, a + b

def fib2(max):
    a,b = 0,1
    def next():
        nonlocal a,b
        if a < max:
                a,b= b,a+b
                return b -a
        else:
            return None

    return next
