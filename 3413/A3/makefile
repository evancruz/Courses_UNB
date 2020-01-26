CC=gcc
CFLAGS= -g -Wall 


main: main.c
	$(CC) main.c -o main -lpthread

clean:
	rm -f main

run: main
	./main 3 < input2.txt

test1:  main
	./main 2 < input1.txt > outputTest1.txt && diff outputTest1.txt expected1.txt > diff1.txt 