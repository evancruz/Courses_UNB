def read_csv(filename):
   '''
   Read a CSV file, and return a list of rows
   '''
   import csv
   with open(filename,'rt',newline='') as f:
      reader = csv.reader(f, skipinitialspace=True)
      return [([category.strip() for category in row ]) for row in reader ]


def  header_map(columnLabels):
   '''
   Builds a dictionary from a list of labels, so that users are able to access labels as a key
   '''
   index = 0
   map = {}
   for label in columnLabels:
      map[label]  = index
      index +=1

   return map


def select(table, columns):
   '''
   Uses header_map to select a new table with the columns specified of the given table
   '''
   tableDictionary = header_map(table[0])
   categoryIndexes = [tableDictionary[label] for label in columns if label in tableDictionary]
   categoryIndexes.sort()

   return [([row[index] for index in categoryIndexes]) for row in table]

def row2dict(headers, row):
   '''
   row2dict that takes the output from header_map and a row, 
   and returns a dictionary representing that row
   '''
 
   return { keys: row[value] for(keys,value) in headers.items()}


def compare(left, operation, right):
   '''
   Arguments:
      left is a value to compare for
      right is a value to compare against
      operation is the comparison operator
   Returns the boolean value of the comparison result
   '''
   if operation == '<=':
      return left <= right
   elif operation == '==':
      return left == right
   else:
      return left >= right


def check_row(row, query):
   '''
   check_row takes a row and a query variable consisting of a 3-tuple of the following assumptions:
   query[0] is a string or an int. If it's a string then check for a label key and if it doesn't exist then it's treated as a literal string.
   If it needs to be treated as a literal string then it also needs to try to convert to an int first to pass the first test
   query[1] has a comparator operator
   query[2] is strictly a value to compare against query [1] (Meaning it's not checked against a column label). It can be a string or an int. 
   If it's a string, it needs to try to be converted to an int to keep the logic similar to the first argument. 
   Another assumption is that only strings will be matched against a column label since we are using csv which is a comma separated text
   
   For the case that query contains a logical operator (AND or OR) then
   I also had to make a strange check in "if not query[1] == '==':" 
   because "if query[1] == 'AND' or 'OR" would still be true for when query[1] == '=='
   '''
   if not query[1] == '==':
      if query[1] == 'OR':
         return check_row(row, query[0]) or check_row(row, query[2])
      elif query[1] == 'AND':
         return check_row(row, query[0]) and check_row(row, query[2])

   left = query[0]
   op = query[1]
   right = query[2]

   if left in row:
      left = row[left]
      try:
         left = int(left)
         right = int(right)
         return  compare(left, op, right)
      except:
         return compare(left, op, right)
   else:
      if type(left) == type (right):
         try:
            left = int(left)
            right = int(right)
            return  compare(left, op, right)
         except:
            return compare(left, op, right)
         
      else:
         if type(left) == str:
            try:
               left = int(left)
               return  compare(left, op, right)
            except:
               return compare(left, op, right)
         else:
            try:
               right = int(right)
               return  compare(left, op, right)
            except:
               return compare(left, op, right)

def filter_table(table,query):
   '''
   assert filter_table(table,('eye colour', '==', 'brown')) == [['name', 'age', 'eye colour'],
                                                                 ['Mary', '27', 'brown']]

    assert filter_table(table,('name', '==', 'Vij')) == [['name', 'age', 'eye colour'],
                                                         ['Vij', '54', 'green']]
   row = {'house': 'Harkonnen', 'origin': 'Hakkon', 'color': 'red', 'enemy': 'Atreides'}
   assert check_row(row, ('house', '==', 'Harkonnen'))

   hmap = header_map(table[0])
    assert row2dict(hmap, table[1]) == {
        'name': 'Bob', 'age': '5', 'eye colour': 'blue'}
   '''
   hmap = header_map(table[0])
   print(hmap)
   headerList = [table[0]]
   print(headerList)
   tableMinusHeader = table [1:]
   print(tableMinusHeader)
   for row in tableMinusHeader:
      rowDictionary = row2dict(hmap, row)
      if check_row(rowDictionary, query):
         headerList = headerList + [row]
   return headerList
         

