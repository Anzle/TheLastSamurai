all: test1 test2 test3 test4

malloc.o: 
	gcc -Wall -g -c malloc.c
	
lib.a: malloc.o
	ar rv lib.a malloc.o

test1: test1.c lib.a
	gcc -Wall -g -o test1 test1.c lib.a -lm 
	
test2: test2.c lib.a
	gcc -Wall -g -o test2 test2.c lib.a -lm

test3: test3.c lib.a
	gcc -Wall -g -o test3 test3.c lib.a -lm
  
test4: test4.c lib.a
	gcc -Wall -g -o test4 test4.c lib.a -lm  

clean:
	rm lib.a malloc.o test1 test2 test3 test4