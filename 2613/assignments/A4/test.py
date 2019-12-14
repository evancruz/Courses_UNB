from main import read_csv, header_map,select,row2dict,check_row, filter_table

def test_read_csv():
    assert read_csv('test1.csv') == [['name', 'age', 'eye colour'],
                                     ['Bob', '5', 'blue'],
                                     ['Mary', '27', 'brown'],
                                     ['Vij', '54', 'green']]
def test_read_csv2():
    assert read_csv('test2.csv') == [['house', 'origin', 'color', 'enemy'],
                                    ['Atreides', 'Atreus', 'green', 'Harkonnen'],
                                    ['Harkonnen', 'Hakkon', 'red', 'Atreides'],
                                    ['Ordos', 'Ordus', 'green', 'Everyone'],
                                    ['Boro', 'Camie', 'yellow', 'Atreides'],
                                    ['Corrino', 'Padisha', 'bronze', 'Harkonnen']]
def test_read_csv3():
    assert read_csv('test3.csv') == []


table = read_csv('test1.csv')
table2 = read_csv('test2.csv')
table3 = read_csv('test3.csv')
def test_header_map_1():
    hmap = header_map(table[0])
    assert hmap == {'name': 0, 'age': 1, 'eye colour': 2}
def test_header_map_2():
    hmap = header_map(table2[0])
    assert hmap == {'house': 0, 'origin': 1, 'color': 2, 'enemy': 3}
def test_header_map_3():
    '''
    Make a non header row to be the header
    '''
    hmap = header_map(table2[1])
    assert hmap == {'Atreides': 0, 'Atreus': 1, 'Harkonnen': 3, 'green': 2}
def test_header_map_4():
    hmap = header_map(table3)
    assert hmap == {}


def test_select_1():
    assert select(table,{'name','eye colour'}) == [['name', 'eye colour'],
                                                ['Bob',  'blue'],
                                                ['Mary', 'brown'],
                                                ['Vij',  'green']]
def test_select_2():
    assert select(table,{'eye colour','name'}) == [['name', 'eye colour'],
                                                ['Bob',  'blue'],
                                                ['Mary', 'brown'],
                                                ['Vij',  'green']]
def test_select_3():
    assert select(table,{'eye colour','height'}) == [['eye colour'], ['blue'], ['brown'], ['green']]
def test_select_4():
    assert select(table,{'sex','height'}) == [[], [], [], []]
def test_select_5():
    assert select(table2,{'house','enemy'}) == [['house', 'enemy'], 
                                             ['Atreides', 'Harkonnen'],
                                             ['Harkonnen', 'Atreides'],
                                             ['Ordos', 'Everyone'],
                                             ['Boro', 'Atreides'],
                                             ['Corrino', 'Harkonnen']]
   
def test_row2dict():
    hmap = header_map(table[0])
    assert row2dict(hmap, table[1]) == {
        'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
def test_row2dict2():
    hmap = header_map(table2[0])
    assert row2dict(hmap, table2[1]) == {
        'house': 'Atreides', 'origin': 'Atreus', 'color': 'green', 'enemy': 'Harkonnen'}


def test_check_row():
    row = {'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
    assert check_row(row, ('age', '==', 5))
    assert not check_row(row, ('eye colour', '==', 5))
    assert check_row(row, ('eye colour', '==', 'blue'))
    assert check_row(row, ('age', '>=', 4))
    assert check_row(row, ('age', '<=', 1000))

def test_check_row2():
    row = {'house': 'Harkonnen', 'origin': 'Hakkon', 'color': 'red', 'enemy': 'Atreides'}
    assert not check_row(row, ('house', '==', 'Atreides'))
    assert check_row(row, ('house', '==', 'Harkonnen'))
    assert check_row(row, ('house', '>=', 'Atreides'))
    assert check_row(row, ('25', '==', '25'))
    assert check_row(row, (6, '>=', '5'))
    assert check_row(row, (99, '<=', 100))
    assert check_row(row, (101, '>=', 100))
    assert check_row(row, ('snow', '<=', 'snow'))
    assert check_row(row, ('shoe', '<=', 'show'))
    assert not check_row(row, ('shoe', '>=', 'show'))
    assert not check_row(row, ('', '==', 'a'))
    assert check_row(row, ('', '==', ''))
    assert check_row(row, ('', '', ''))

def test_check_row_logical():
    row = {'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
    assert check_row(row, (('age', '==', 5),'OR',('eye colour', '==', 5)))
    assert check_row(row, (('6', '==', 5),'OR',('eye colour', '==', 'blue')))
    assert not check_row(row, (('6', '==', 5),'OR',('eye colour', '==', 'red')))
    assert not check_row(row, (('age', '==', 5),'AND',('eye colour', '==', 5)))



def test_filter_table1():
    assert filter_table(table,('age', '>=', 0)) == [['name', 'age', 'eye colour'],
                                                    ['Bob', '5', 'blue'],
                                                    ['Mary', '27', 'brown'],
                                                    ['Vij', '54', 'green']]

    assert filter_table(table,('age', '<=', 27)) == [['name', 'age', 'eye colour'],
                                                     ['Bob', '5', 'blue'],
                                                     ['Mary', '27', 'brown']]

    assert filter_table(table,('eye colour', '==', 'brown')) == [['name', 'age', 'eye colour'],
                                                                 ['Mary', '27', 'brown']]

    assert filter_table(table,('name', '==', 'Vij')) == [['name', 'age', 'eye colour'],
                                                         ['Vij', '54', 'green']]

def test_filter_table2():
    assert filter_table(table,(('age', '>=', 0),'AND',('age','>=','27'))) == [['name', 'age', 'eye colour'],
                                                                              ['Mary', '27', 'brown'],
                                                                              ['Vij', '54', 'green']]


    assert filter_table(table,(('age', '<=', 27),'AND',('age','>=','27'))) == [['name', 'age', 'eye colour'],
                                                                               ['Mary', '27', 'brown']]

    assert filter_table(table,(('eye colour', '==', 'brown'),
                               'OR',
                               ('name','==','Vij'))) == [['name', 'age', 'eye colour'],
                                                        ['Mary', '27', 'brown'],
                                                        ['Vij', '54', 'green']]