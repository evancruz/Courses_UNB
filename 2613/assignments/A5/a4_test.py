from Ledger import Type, Token, __str__

def test_enum():
    '''check that defined enum type matches assignment'''

    assert sorted([ member.name for member in Type ]) == ["BALANCE", "CURRENCY", "IDENT", "OPEN", "TRANSFER"]

def test_enum2():
    assert sorted([ member.name for member in Type ]) != ["baLanc", "MONEYCASH", "IDENT", "CLOSE", "TRANSFER"]

def test_token():
    token=Token(Type.IDENT,"hello")
    assert token.type==Type.IDENT
    assert token.value=="hello"

def test_token_rest():
    '''I make the assumption that CURRENCY values will always be inputted correctly as digits, not as strings. 
    Also, that I am to "store the text as the user typed it in the value property" '''
    token=Token(Type.BALANCE,"bAlAnCe")
    assert token.type==Type.BALANCE
    assert token.value!="balAnCe"
    assert token.value=="bAlAnCe"
    token=Token(Type.CURRENCY,123456789)
    assert token.type==Type.CURRENCY
    assert token.value==123456789
    token=Token(Type.OPEN,'NOTOPEN')
    assert token.type==Type.OPEN
    assert token.value=='NOTOPEN'
    token=Token(Type.TRANSFER,'TRANSFER')
    assert token.type!=Type.OPEN
    assert token.value=='TRANSFER'


def test_str():
    id=Token(Type.IDENT,"hello")
    assert str(id) == '[IDENT: hello]'
    money=Token(Type.CURRENCY,10042)
    assert str(money) == '[CURRENCY: 100.42]'

def test_str2():
    id=Token(Type.IDENT,"all_your_BASE_are_belong_to_us!")
    assert str(id) == '[IDENT: all_your_BASE_are_belong_to_us!]'
    money=Token(Type.CURRENCY,1)
    assert str(money) == '[CURRENCY: 0.01]'
    open = Token(Type.OPEN,"OPEN")
    assert str(open) == '[OPEN: OPEN]'

def test_equal_ident():
    assert Token(Type.IDENT,"Bob") == Token(Type.IDENT,"Bob")
    assert Token(Type.IDENT,"Bob") != Token(Type.IDENT,"bOb")

def test_equal_keywords():
    assert Token(Type.TRANSFER,"transfer") != Token(Type.OPEN,"open")
    assert Token(Type.OPEN,"OPEN") == Token(Type.OPEN,"open")
    assert Token(Type.BALANCE,"BALANCE") == Token(Type.BALANCE,"balance")

def test_equal_keywords2():
    assert Token(Type.OPEN,"OPEN") != Token(Type.IDENT,"OPEN")
    assert Token(Type.TRANSFER,"Transfer") != Token(Type.IDENT,"bOb")
    assert Token(Type.OPEN,"OpEn") == Token(Type.OPEN,"OPEN")

def test_equal_currency():
    assert Token(Type.CURRENCY,1000) == Token(Type.CURRENCY,1000)
    assert Token(Type.CURRENCY,1000) != Token(Type.CURRENCY,1001)

def test_equal_currency2():
    assert Token(Type.CURRENCY,-99999999999999999999999999999999999) == Token(Type.CURRENCY,-99999999999999999999999999999999999)
    assert Token(Type.CURRENCY,.000000000000000000000000000000000000000000001) == Token(Type.CURRENCY,.000000000000000000000000000000000000000000001)

# def test_scan_keywords():
#     scanner=Scanner('''TrAnsFer transfer 
#                        OPEN BALANCE balance''')
#     toks = [Token(Type.TRANSFER,"TrAnsFer"), Token(Type.TRANSFER,"transfer"),
#             Token(Type.OPEN,"OPEN"),
#             Token(Type.BALANCE,"BALANCE"),  Token(Type.BALANCE,"balance")]

#     assert [tok for tok in scanner] == toks
#     # iterate a second time
#     assert [tok for tok in scanner] == toks

# def test_scan_identifiers():
#     scanner=Scanner("equity cash end_of_the_world_fund")
#     assert list(scanner) == [Token(Type.IDENT,"equity"),
#                                         Token(Type.IDENT,"cash"),
#                                         Token(Type.IDENT,"end_of_the_world_fund")]