iris = csvread("iris.csv");

[training, testing] = randomsplit(iris, 2/3)

p = 2
cells = p^(columns(iris)-1)+1

minmax = ranges(iris);
classes = minmax(2,1) - minmax(1,1) + 1;

votes = zeros(cells,classes);

for i=1:rows(training)
  label = training(i,1);
  hashval = hash(training(i,:), minmax, p);
  votes(hashval,label) += 1;
endfor

classification = tally(votes)

correct = 0
for i=1:rows(testing);
  hashval = hash(testing(i,:), minmax, p);
  class=classification(hashval);
  label = testing(i,1);
  if label == class
    correct += 1;
  endif
endfor

display(correct/rows(testing))
