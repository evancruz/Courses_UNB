load training
load testing
timeit(1000,@nearest,testing(1,:), 3, training);
%take row 1 of testing and pass in the matrix training

timeit(10,@knn,3,training,testing);
timeit(10,@knn2,3,training,testing);
timeit(10,@rowknn,3,training,testing);