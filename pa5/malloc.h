#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int		isFree;
	int		size;
}MemEntry;

void * mymalloc(unsigned int, char*, int);
void myfree(void *, char*, int);

int* ptrBound();
void clearMemory();
void printMemory();

#endif