''' unicode 
   uni_snake = "I love \N{ROOSTER}"
   print(uni_snake)
'''

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

'''
CHAPTER 1
   1.1 FUNCTIONS
   
   def approximate_size(size, a_kilobyte_is_1024_bytes=True):
      #program code
   
   Every Python function returns a value; if the function ever executes a return statement, it will return that value, otherwise it will return None, the Python null value.)



   1.2 LIBRARY SEARCH PATH
   Python looks in several places when you try to import a module. Specifically, it looks in all the directories defined in sys.path. This is just a list, and you can easily view it or modify it with standard list methods. (You’ll learn more about lists in Native Datatypes.)

   import sys
   sys.path
   sys.path.insert(0, '/home/mark/diveintopython3/examples')

   By using sys.path.insert(0, new_path), you inserted a new directory as the first item of the sys.path list, and therefore at the beginning of Python’s search path. This is almost always what you want. In case of naming conflicts (for example, if Python ships with version 2 of a particular library but you want to use version 3), this ensures that your modules will be found and used instead of the modules that came with Python.



   1.3 EVERYTHING IS AN OBJECT (DOC)

   import humansize 
   print(humansize.approximate_size.__doc__)
      Once you import a Python module, you access its functions with module.function

   In Python, functions are first-class objects. You can pass a function as an argument to another function. Modules are first-class objects. You can pass an entire module as an argument to a function. Classes are first-class objects, and individual instances of a class are also first-class objects.



   1.4 EXCEPTIONS

   Some programming languages encourage the use of error return codes, which you check. Python encourages the use of exceptions, which you handle.
   Unlike Java, Python functions don’t declare which exceptions they might raise. It’s up to you to determine what possible exceptions you need to catch.

   1.5 Modules 
   So what makes this if statement special? Well, modules are objects, and all modules have a built-in attribute __name__. A module’s __name__ depends on how you’re using the module. If you import the module, then __name__ is the module’s filename, without a directory path or file extension.

>>> import humansize
>>> humansize.__name__
'humansize'
But you can also run the module directly as a standalone program, in which case __name__ will be a special default value, __main__.

'''





'''
Chapter 2 
TYPES/LISTS/TUPLES
   Lists are ordered sequences of values.
   Tuples are ordered, immutable sequences of values.
   Sets are unordered bags of values.
   Dictionaries are unordered bags of key-value pairs.

   Everything is an object in Python, so there are types like module, function, class, method, file, and even compiled code. 

   Slice
   a_list = ['a', 'b', 'mpilgrim', 'z', 'example']
   a_list[1:3] -> gives ['b', 'mpilgrim']
   a_list[:] -> copies entire array

   Add to List/Delete
   a_list = ['a']
   a_list = a_list + [2.0, 3]
   a_list.append(True)           
   a_list.extend(['four', 'Ω'])  ④
   >>> a_list
      [ 'a', 2.0, 3, True, 'four', 'Ω']
   a_list.insert(0, '>')         ⑤
   >>> a_list
      [ '>', 'a', 2.0, 3, True, 'four', 'Ω']
   del a_list[1] 
   a_list.remove('four')
   a_list.pop()
   a_list.pop(0)
   
   Searching For Values In A List
   a_list = ['a', 'b', 'new', 'mpilgrim', 'new']
   >>> a_list.count('new')       ①
   2
   >>> 'new' in a_list           ②
   True
   >>> a_list.index('mpilgrim')  ③
   3

   Boolean in Lists
   1. In a boolean context, an empty list is false.
   2. Any list with at least one item is true.

   

   TUPLES
   a_tuple = ("a", "b", "mpilgrim", "z", "example")
   You can slice a tuple (because that creates a new tuple)and you can check whether a tuple contains a particular value

   Tuples are faster than lists. If you’re defining a constant set of values and all you’re ever going to do with it is iterate through it, use a tuple instead of a list.

   Some tuples can be used as dictionary keys (specifically, tuples that contain immutable values like strings, numbers, and other tuples). Lists can never be used as dictionary keys, because lists are not immutable.

   Tuples can be converted into lists, and vice-versa. tuple() function takes a list and returns a tuple with the same elements, and the list() function takes a tuple and returns a list. 



   SETS   >>> a_set = {1}
   A set is an unordered “bag” of unique values. A single set can contain values of any immutable datatype. Once you have two sets, you can do standard set operations like union, intersection, and set difference.

   a_set.add(4)
   len(a_set)
   >>> 30 in a_set
      false

   

   DICTIONARIES 
   Python dictionaries are optimized for retrieving the value when you know the key, but not the other way around.

   a_dict = {'server': 'db.diveintopython3.org', 'database': 'mysql'}
   a_dict['server']
   a_dict['user'] = 'mark'
'''

'''
   Chapter 3

   Comprehensions
   A list / dictionary comprehension provides a compact way of mapping a list into another list by applying a function to each of the elements of the list.

   a_list = [elem * 2 for elem in a_list]
   metadata = [(f, os.stat(f)) for f in glob.glob('*test*.py')]


   Filter:
   [f for f in glob.glob('*.py') if os.stat(f).st_size > 6000]



   Python 3 supports formatting values into strings. Although this can include very complicated expressions, the most basic usage is to insert a value into a string with a single placeholder.

username = 'mark'
password = 'PapayaWhip' 
>>> "{0}'s password is {1}".format(username, password)  
   "mark's password is PapayaWhip"


'''
