all: main test2

malloc.o: 
	gcc -Wall -g -c malloc.c
	
lib.a: malloc.o
	ar rv lib.a malloc.o

main: main.c lib.a
	gcc -Wall -g -o main main.c lib.a -lm 
	
test2: test2.c lib.a
	gcc -Wall -g -o test2 test2.c lib.a -lm
	
clean:
	rm lib.a main malloc.o test2