import csv


def read_csv(filename):
   '''
      Read a CSV file, return list of rows
   '''
   aList = [];
   with open(filename, newline='') as f:
      reader = csv.reader(f)

      for row in reader:
         aList.append(row);
         #print(aList)
   return aList;

someList = read_csv('test1.csv')
print(someList);


def header_map (list):
   for 
   #assert hmap == { 'name': 0, 'age': 1, 'eye colour': 2 }

print(header_map(someList[0]));
