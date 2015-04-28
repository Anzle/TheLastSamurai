#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int		isFree;
	int		size;
}MemEntry;

void * mymalloc(unsigned int);
void myfree(void *);

#endif