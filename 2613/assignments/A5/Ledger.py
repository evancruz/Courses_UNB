from enum import Enum
import re

class Type(Enum):
    '''The set of members allowed for our ledger system'''
    BALANCE = 1
    CURRENCY = 2
    IDENT = 3
    OPEN = 4
    TRANSFER = 5

class Token:
    ''' Each token will be an instance of this class made up of a Type and value'''
    def __init__(self, type, value):
        '''Initializes an instance of Token'''
        self.type = type
        self.value = value

    def __str__(self):
        '''Pretty prints this instance. Int values are multiplied by .01 to be able to print with dollars and cents'''
        if type(self.value) == int:
            val = self.value*.01
            return '[' + self.type.name + ': ' + str(val) + ']'
        else:
            return '[' + self.type.name + ': ' + str(self.value) + ']'

    def __eq__(self, other):
        '''Comparison method. Keywords are case insensitive but user defined (IDENT) are case sensitive'''
        if sameType(self, other):
            return checkEquality(self, other)
        else:
            return False

def sameType(A, B):
    ''' Checks if the two objects passed in are the same type'''
    if A.type.name == B.type.name:
        return True
    else:
        return False

def checkEquality(A, B):
    '''Checks if the two objects are equal (they will always be same type). If it is IDENT it checks for case sensitivity, 
    and if it is CURRENCY then checks for value. All other cases are True
    '''
    if A.type.name == 'IDENT'or A.type.name == 'CURRENCY':
        return A.value == B.value 
    else:
        return True


# class Scanner:

#     def __init__(self, tokens):
#         print("init")
#         self.tokens = tokens
        

#     def __iter__(self):
#         # reset counter
#         print("in iter") 
#         return self
    
#     def __next__(self):
#         print("cont")
        
#         # strip_regex = re.compile(r'"?([^"]+)"?')
#         # regex 
#         # prevent words from beginning with symbol
#         # strip whitespace
#         # raise stop iteration
        
# scanner=Scanner('''TrAnsFer transfer 
#                        OPEN BALANCE balance''')
                       
# print([tok for tok in scanner])










