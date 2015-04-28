

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

#define BLOCKSIZE(1024 * 1024)
static char BigBlock(BLOCKSIZE);


void * mymalloc(unsigned int size){
	static int				initialized = 0;
	static structMemEntry	*root = 0, *last = 0;
	struct MemEntry			*p, *succ;
	
	
	if(!initialized){
		root = (struct MemEntry *) BigBlock;
		root->prev = 0;
		root->succ = 0;
		root->size = BLOCKSIZE - sizeof(struct MemEntry);
		root->isFree = 1;
		initialized = 1;
	}
	
	p = root;
	do{
		if(p->size < size)//If too small, skip it
			p= p->succ;
		else if(!p->isFree) //If not free, skip it
			p= p->succ;
		else if(p->size < (size + sizeof(struct MemEntry))){ //Is it too small to chop up?
			p->isFree = 0;
			return (char *)p + sizeof(struct MemEntry); //return the pointer after the MemEntry struct p
			//return p + 1; //This should also work
			}
		else{
			succ = (struct MemEntry*)((char*)p + sizeof(struct MemEntry) + size); //where am I going to put the next mementry struct. Physically
			succ -> prev = p;
			succ->succ = p-> succ;
			if(p->succ != 0)
				p->succ->prev = succ;
			p-> succ = succ;
			succ->size = p->size - sizeof(struct MemEntry) - size;
			succ->isFree = 1;
			p->size = size;
			p->isFree = 0;
			return (char*)p + sizeof(struct MemEntry);
		}
	}while(p != 0);
	if((p = (struct MemEntry *) sbrk(sizeof(struct MemEntry) + size)) == (void*)-1){
		return 0;
	}
	else if(last == 0){ //create/init block
		p->prev = p->succ = 0;
		p->size = 0;
		p->isFree= 0;
		root = last = p;
		return (char*) p + sizeof(struct MemEntry);
	}
	else { //append
		p->prev = last;
		p->succ = last->succ; //0
		p->size = size;
		p->isFree = 0;
		last->succ = p;
		last = p;
		return p+1;
	}
	
	return 0;
}//End myMalloc

void myFree(void * p){
	struct MemEntry		*prt, *pred, *succ;

	ptr = (struct MemEntry*)((char*)p - sizeof(struct MemEntry));
	if((pred = prt->prev) != 0 && pred->isFree){
		pred->size += sizef(struct MemEntry) + prt->size;
		pred->succ = ptr->succ;
		
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	}
	else{
		ptr->isFree = 1;
		pred = ptr;
	}
	
	if((succ = ptr->succ) != 0 && succ->isFree){
		pred->size += sizeof(struct MemEntry) + succ->size;
		pred->succ = succ->succ;
		if(succ->succ !=0)
			succ->succ->prev = pred;
	}
}