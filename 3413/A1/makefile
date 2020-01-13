CC=gcc
CFLAGS= -g -Wall


main: main.c
	$(CC) main.c -o main

clean:
	rm -f main

test1:  main
	./main 2 < input1.txt > outputTest1.txt && diff outputTest1.txt expected1.txt > diff1.txt 

test2:  main
	./main 3 < input1.txt > outputTest2.txt && diff outputTest2.txt expected2.txt > diff2.txt 

test3:  main
	./main 2 < input2.txt > outputTest3.txt && diff outputTest3.txt expected3.txt > diff3.txt 