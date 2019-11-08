import csv

def read_csv(filename):
   '''
      Read a CSV file, and return a list of rows
   '''
   lstOfCategories = []
   with open(filename, newline='') as f:
      reader = csv.reader(f)
      return [([category.strip() for category in row ]) for row in reader]

   

testList1 = read_csv('test1.csv')
for row in testList1:
   print(row)


def  header_map(columnLabels):
   '''
      Builds a dictionary from a list of labels, so that users are able to access labels as a key
   '''
   index = 0;
   map = {};
   for label in columnLabels:
      map[label]  = index;
      index +=1;

   return map


hmap = header_map(testList1[0])




def select(table, columns):
   '''
      something something
       Use your implimentation of header_map to write a function select that creates a new table with some of the columns of the given table.
   '''
   selectedTable = []
   categoryIndexes = [];
   tableDictionary = header_map(table[0])
   for label in columns:
      if label in tableDictionary:
         categoryIndexes.append(tableDictionary[label])
   categoryIndexes.sort()

   for row in range(0, len(table)):
      for index in categoryIndexes:
         selectedTable.append(table[row][index])
   return selectedTable



select(testList1, {'name', 'eye colour'})

def row2dict(headers, row):
   '''
   row2dict that takes the output from header_map, and a row, and returns a dictionary representing that row (column order is lost here, but that will be ok in our application

    hmap = header_map(table[0])
    assert row2dict(hmap, table[1]) == {
        'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
   '''
 
   return { keys: row[value] for(keys,value) in headers.items()}

testRow = row2dict(hmap, testList1[1])
print(testRow)

def check_row(row, ops):
   '''
      write a query languge where each query is a 3-tuple (left, op, right), and op is one of ==, <=, and >=. In the initial version, left and right are numbers or strings. Strings are interpreted as follows: if they are column labels, retrieve the value in that column; otherwise treat it as a literal string. With this in mind, write a function check_row that takes a row in dictionary form, and checks if it matches a query tuple.
      row = {'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
      assert check_row(row, ('age', '==', 5))
      assert not check_row(row, ('eye colour', '==', 5))

      I AM ASSUMING CHECK ROW DOES THE FOLLOWING:
      TUPLE[0]CHECKS FOR A COLUMN LABEL KEY AND GRABS THE VALUE (IF IT DOESN"T EXIST THEN JUST TREAT AS LITERAL STRING)
      THEN TUPLE[1] HAS THE COMPARATOR OPERATOR
      THEN TUPLE[2] IS THE VALUE THAT IS BEING COMPARED TO TUPLE[1] (TUPLE[2] IS STRICTLY A VALUE TO COMPARE AND NOT A COLUMN LABEL)
   '''
   #check_row(row, ops):
   left = ops[0]
   middle = ops[1]
   right = ops[2]


   #if left in columslabel
      #get val
      #val operator right (assuming right is only compared not having to look up)
   if left in row:
      #means it is a string because csv is a comma separated text
      #and need to try converting to int first before comparing strings to pass first given test
      val = row[left]
      try:
         return int(val) == right
      except:
         return val == right
   else:
      #it is either  not a key String or is a number


   
   

print('\n')
print(check_row(testRow, ('boogey', '==', 5)))
print(check_row(testRow, ('snow', '==', 'snow')))
print(check_row(testRow, ('age', '==', 5)))
print(check_row(testRow, ('eye colour', '==', 'blue')))


