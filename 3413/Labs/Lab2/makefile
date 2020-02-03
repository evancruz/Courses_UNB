CC=gcc
CFLAGS= -g -lpthread


main: main.c
	$(CC) $(CFLAGS) main.c -o main

main2: main2.c
	$(CC) $(CFLAGS) main2.c -o main2

clean:
	rm -f main

test:  main
	./main < input1.txt