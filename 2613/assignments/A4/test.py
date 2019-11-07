
import main
from main import read_csv
def test_read_csv():
    print(read_csv('test1.csv'))
    assert read_csv('test1.csv') == [['name', 'age', 'eye colour'],
                                     ['Bob', '5', 'blue'],
                                     ['Mary', '27', 'brown'],
                                     ['Vij', '54', 'green']]


