all: set.o avl.o llrbt.o main.o
	gcc avl.o llrbt.o set.o main.o -o main -std=c99 -Wall
	rm *.o

set.o:
	gcc -c set.c -o set.o

avl.o:
	gcc -c avl.c -o avl.o

llrbt.o:
	gcc -c llrbt.c -o llrbt.o

main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o main

run:
	./main