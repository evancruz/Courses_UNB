import sys
import keyword

d = {'hello': 'world'}

print (d.get('world', 'efault_value')) # prints 'world'
print (d.get('asdkasjd', 'default_value')) # prints 'default_value'

# Or:
#if 'hello' in d:
#    print (d['hello'])

names = []
names.append("evan")
names.append("cruz")
print(names)

uni_snake = "I love \N{ROOSTER}"
print(uni_snake)


# “>> > a is b
# True
# >> > a is not b
# False
# "is" is faster than == and connotes to the programmer
# that identity is being compared rather than the value.

