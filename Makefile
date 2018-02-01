CC = gcc
FLAGS = #-ansi -pedantic -Wall -Werror

OBJC = Queue.o main.o 

.PHONY : clean

Queue.o: Queue.c Queue.h
	$(CC) Queue.c -g -c -o  Queue.o $(FLAGS)

main.o: main.c Queue.h
	$(CC) main.c -g -c -o main.o $(FLAGS)

utest.o : utest.c Queue.h mu_test.h
	$(CC) utest.c -g -c -o utest.o $(FLAGS)

test : $(OBJC) 
	$(CC) $(OBJC) -o test

utest : Queue.o utest.o
	$(CC) Queue.o utest.o -o utest

clean: 
	rm -f $(OBJC) libds.so 
