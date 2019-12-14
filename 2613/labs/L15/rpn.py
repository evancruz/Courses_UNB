#!/usr/bin/python3

import sys

stack = []

def _arith(op, a,b):
    if op == "+":
        stack.append(a+b)
    elif op == "-":
        stack.append(a-b)
    elif op == "/":
        stack.append(a//b)
        # the floor of a/b is a//b
    elif op == "*":
        stack.append(a*b)
    # elif op == "swap":
    #     stack.append(a)
    #     stack.append(b)

def process(line):
    if line in ["+", "-", "/", "*"]:
        b=stack.pop()
        a=stack.pop()
        _arith(line, a,b)
    elif line == "clear":
        stack.clear()
    elif line == "print":
        return int(stack[-1])
    elif line == "dup":
        stack.append(stack[-1])
    elif line == "pop":
        stack.pop()
    elif line == "swap":
        stack.swap()
    else:
        stack.append(int(line))
    

def process_list(lines):
    out = []
    for line in lines:
        if line == "quit":
            break
        retv = process(line)
        if retv:
            #does not equal None (undefined)
            out.append(process(line))
    return out





if __name__ == '__main__':
    ops=[]
    for line in sys.stdin:
        line = line.strip()
        ops.append(line)

    out = process_list(ops)
    for line in out:
        print(line)









# def uncovered(thing):
#     pass

