#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//I can't pull
struct MemEntry{
	struct MemEntry *prev, *succ;
	int		isFree;
	int		size;
}

void * mymalloc(unsigned int);
void myfree(void *);

#endif