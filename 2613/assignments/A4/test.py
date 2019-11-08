from main import read_csv

def test_read_csv():
    assert read_csv('test1.csv') == [['name', 'age', 'eye colour'],
                                     ['Bob', '5', 'blue'],
                                     ['Mary', '27', 'brown'],
                                     ['Vij', '54', 'green']]


table = read_csv('test1.csv')
def test_header_map_1():
    hmap = header_map(table[0])
    assert hmap == {'name': 0, 'age': 1, 'eye colour': 2}


def test_row2dict():
    hmap = header_map(table[0])
    assert row2dict(hmap, table[1]) == {
        'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
