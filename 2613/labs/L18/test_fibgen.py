import fibgen
def test_fib():
    fun = fibgen.fib2(1000)
    lst2 = []
    while True:
        n = fun()
        if n!=None:
            lst2.append(n)
        else:
            break
    assert lst2 == list(fibgen.fib(1000))
