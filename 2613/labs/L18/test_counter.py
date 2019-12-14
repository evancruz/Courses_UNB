
import counter

def test_count():
    counter1=counter.make_counter(100)
    counter2=counter.make_counter2(100)

    for j in range(0,100):
        assert next(counter1) == counter2()

'''
print('first')
counter = make_counter(100)
print('second')
print(next(counter))
print('third')
print(next(counter))
print('last')
'''