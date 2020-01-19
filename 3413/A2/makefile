CC=gcc
CFLAGS= -g

main: main.c
	$(CC) $(CFLAGS) main.c -o main

main2: main2.c
	$(CC) $(CFLAGS) main2.c -o main2

clean:
	rm -f main

test1:  main
	./main 3 < input1.txt

test2:  main
	./main 3 < input2.txt

test3:  main
	./main 2 < input3.txt

test4:  main
	./main 3 < input4.txt