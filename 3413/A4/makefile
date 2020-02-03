CC=gcc
CFLAGS= -g -lpthread
DEBUG= -Wall -g


main: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main

main2: main2.c
	$(CC) $(CFLAGS) main2.c -o main2

clean:
	rm -f main

test:  main
	./main 100