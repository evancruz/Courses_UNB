from client import approximate_size

def test_1k():
    assert approximate_size(1024) == '1.0 KB'

def test_doc():
    assert approximate_size.__doc__ != None