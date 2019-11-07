import csv

def read_csv(filename):
   '''
      Read a CSV file, return list of rows
   '''
   lstOfCategories = []
   with open(filename, newline='') as f:
      #reader = csv.reader(f, delimiter=',')
      reader = csv.reader(f)

      for row in reader:
         lstOfCategories.append([category.strip() for category in row])
   return lstOfCategories

someList = read_csv('test1.csv')
print()
print(someList)


#def header_map (list):
   #for 
   #assert hmap == { 'name': 0, 'age': 1, 'eye colour': 2 }

#print(header_map(someList[0]));
