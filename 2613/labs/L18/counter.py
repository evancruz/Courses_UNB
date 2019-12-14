#!!/usr/bin/python3
def make_counter(x):
    print('entering make_counter')
    while True:
        yield x
        #yield -> makes the function a list generator
        #saves memory 
        print('incrementing x')
        x = x + 1

print('first')
counter = make_counter(100)
print('second')
print(next(counter))
print('third')
print(next(counter))
print('last')


def make_counter2(x):
    count = x
    def counter():
        nonlocal count
        if count == x:
            print("entering make counter 2")
        count = count + 1
        return count - 1




    return counter
