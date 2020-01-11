CC=gcc
CFLAGS= -g -Wall


main: main.c
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f main

test1:  main
	./main 2 < input1.txt 