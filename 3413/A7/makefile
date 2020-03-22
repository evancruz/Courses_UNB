CC=gcc
CFLAGS= -g -lpthread
DEBUG= -Wall -g

main: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main

clean:
	rm -f main output*

testall: test1 test2 test3

test1:  main
	./main 5 < test1.txt > output1.txt

test2:  main
	./main 100 < test2_negative.txt > output2.txt

test3:  main
	./main 10 < test3.txt > output3.txt

