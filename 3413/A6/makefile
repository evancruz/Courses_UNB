CC=gcc
CFLAGS= -g -lpthread
DEBUG= -Wall -g

main: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main

clean:
	rm -f main

test:  main
	./main < 1.txt

test2:  main
	./main -s 501 -f < 2.txt

test3:  main
	./main < input3.txt