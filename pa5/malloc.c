

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

/* Project requres a size 5000 block in the array myblock*/
#define BLOCKSIZE 5000
static char myblock(BLOCKSIZE); /* Dynamic memory in static memory! */


void * mymalloc(unsigned int size){
  //Statics initialized on the first call only
	static int				initialized = 0;
	static MemEntry	  *root = 0, *last = 0;
	MemEntry		*p, *succ;
	
	
	if(!initialized){
		root = (MemEntry *) myblock;
		root->prev = 0;
		root->succ = 0;
		root->size = BLOCKSIZE - sizeof(MemEntry);
		root->isFree = 1;
		initialized = 1;
	}
	
	p = root;
  do{
		if(p->size < size)//If too small, skip it
			p= p->succ; //If p->succ is 0, we will break out
		else if(!p->isFree) //If not free, skip it
			p= p->succ;                                        
		else if(p->size < (size + sizeof(MemEntry))){ //Memory block to small to chop
      /**Wouldn't this allow us to write past the end? Or into something else?**/
			p->isFree = 0;  
			return (char *)p + sizeof(MemEntry); //return the pointer after the MemEntry struct p
			//return p + 1; //This should also work
			}
		else{//where am I going to put the next mementry struct. I'm also chopping up blocks
			succ = (MemEntry*)((char*)p + sizeof(MemEntry) + size); 
			
      succ -> prev = p;
			succ->succ = p-> succ;
			
      if(p->succ != 0)
				p->succ->prev = succ;
			
      p-> succ = succ;
			
      succ->size = p->size - sizeof(MemEntry) - size;
			succ->isFree = 1;
			
      p->size = size;
			p->isFree = 0;
			
      return (char*)p + sizeof(MemEntry);
		}
	}while(p != 0);
	

  // sbrk() increments the program's data space by increment bytes.
  // if it advances to far, then we are out of space. Kill it. 
  if((p = (MemEntry *) sbrk(sizeof(MemEntry) + size)) == (void*)-1)
		return 0;
	
  else if(last == 0){ //create/init block
		p->prev = p->succ = 0;
		p->size = 0;
		p->isFree= 0;
		
    root = last = p;
		return (char*) p + sizeof(MemEntry);
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
	MemEntry		*prt, *pred, *succ;

	ptr = (MemEntry*)((char*)p - sizeof(MemEntry));
	if((pred = prt->prev) != 0 && pred->isFree){
		pred->size += sizef(MemEntry) + prt->size;
		pred->succ = ptr->succ;
		
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	}
	else{
		ptr->isFree = 1;
		pred = ptr;
	}
	
	if((succ = ptr->succ) != 0 && succ->isFree){
		pred->size += sizeof(MemEntry) + succ->size;
		pred->succ = succ->succ;
		if(succ->succ !=0)
			succ->succ->prev = pred;
	}
}