CC=gcc
CFLAGS= -g -lpthread
DEBUG= -Wall -g

main: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main

clean:
	rm -f main

test:  main
	./main 10 < test1.txt