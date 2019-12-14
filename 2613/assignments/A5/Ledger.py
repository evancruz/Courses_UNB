from enum import Enum

class Type(Enum):
    BALANCE = 1
    CURRENCY = 2
    IDENT = 3
    OPEN = 4
    TRANSFER = 5

class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value

    # def __str__(self):
    #     return '[' + self.type.name + ': ' + str(self.value) + ']'

    # def __eq__(self, other):
    #     # ident is case sensitive.



# vars(self) == vars (other)  turns it into a dictionary
print(Token(Type.IDENT,"Bob") == Token(Type.IDENT,"Bob"))
# def test_equal_ident():
#     assert Token(Type.IDENT,"Bob") == Token(Type.IDENT,"Bob")
#     assert Token(Type.IDENT,"Bob") != Token(Type.IDENT,"bOb")



