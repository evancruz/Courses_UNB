{}
from arithseq import ArithSeq

def test_evens():
    assert [ x for x in ArithSeq(0,2,10) ] == [0,2,4,6,8,10]

def test_odds():
    assert [ x for x in ArithSeq(1,2,10) ] == [1,3,5,7,9]