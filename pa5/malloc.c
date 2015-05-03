

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

/* Project requres a size 5000 block in the array myblock
the threshhold is for when to allocate to teh front or rear of the list*/
#define BLOCKSIZE 5000
#define THRESH    16

/* Dynamic memory in static memory! */
static char myblock[BLOCKSIZE]; 


/*mymalloc only uses a finite amount of space*/
void * mymalloc(unsigned int size, char* file, int line, const char* func){
  //Statics initialized on the first call only
	static int				initialized = 0;
	static MemEntry	  *root = 0, *last = 0;
	void * retVal;
	//MemEntry		*p, *succ;
	
	
	if(!initialized){
		root = (MemEntry *) myblock;
		root->prev = 0;
		root->succ = 0;
		root->size = BLOCKSIZE - sizeof(MemEntry);
		root->isFree = 1;
		root->pattern = (int)0x55555555;
		initialized = 1;
		last = root; //For reverse allocation
	}
	if(size <= THRESH)
		retVal = backwardMalloc(size, file, line, func, last);
	else
		retVal = forwardMalloc(size, file, line, func, root);
	
	if (retVal)
		printf("Successfully allocated %ld blocks\n", (size+sizeof(MemEntry)));
	return retVal;  
  
}//End myMalloc

void myfree(void * p, char* file, int line){
	MemEntry		*ptr, *pred, *succ;
	
	if(p < myblock || p > myblock + BLOCKSIZE){
		printf("Error: Memory Not Allocated %s:%d\n", file, line);
		return;
	}
	ptr = (MemEntry*)((char*)p - sizeof(MemEntry));
	if(ptr->pattern != 0x55555555){
		printf("Error: Memory Not Allocated via malloc() %s:%d\n", file, line);
		return;
	}
	if((pred = ptr->prev) != 0 && pred->isFree){
		pred->size += sizeof(MemEntry) + ptr->size;
		pred->succ = ptr->succ;
		
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	}
	else{
		if(ptr->isFree == 1){
			printf("Error: Memory Already Freed %s:%d\n", file, line);
			return;
		}
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

/*This is a testing function that tells us the end of the current computing space.
AKA the End of our Stack. Because of this, I might want to remove sbrk from the code above. */
int* ptrBound(){
  return (int*)sbrk(0);
}

/*Clear out the memory by filling the myblock array with 0s*/
void clearMemory(){
  int   i;
  for(i=0;i<BLOCKSIZE;i++)
    myblock[i] = 0;
}

void printMemory(){
  int    i;
  for(i=0;i<BLOCKSIZE;i++)
    printf("%x", myblock[i]);
  printf("\n");
}

void remainingSpace(){
	if()
}

void * backwardMalloc(unsigned int size, char* file, int line, const char* func, MemEntry* last){
  MemEntry *p, *succ;
  p = last;
  do{
		if(p->size < size)//If too small, skip it
			p= p->prev; 
		else if(!p->isFree) //If not free, skip it
			p= p->prev;                                        
		else if(p->size < (size + sizeof(MemEntry))){ 
			p->isFree = 0;  
			return (char *)p + sizeof(MemEntry); //return the pointer after the MemEntry struct p
		}
		else{
			//Create a memory block up the tail of the list
			succ = (MemEntry*)((char*)p + p->size - (sizeof(MemEntry) + size)); 
			succ->pattern = (int)0x55555555;
			succ -> prev = p;
			succ->succ = p-> succ;
			
			if(p->succ != 0)
				p->succ->prev = succ;
					
			p-> succ = succ;
					
			succ->size = sizeof(MemEntry) + size;
			succ->isFree = 0;
					
		    p->size = p->size - succ->size;
			p->isFree = 1;
					
		    //move last down the list
		    if(last->succ == succ)
				last = succ;
			  
			return (char*)succ + sizeof(MemEntry);
		}
	}while(p != 0);
  printf("Out of Space for allocation %s:%s:%d\n", file, func, line);
  return 0;
}

void * forwardMalloc(unsigned int size, char* file, int line, const char* func, MemEntry* root, MemEntry* last){
  MemEntry *p, *succ;
  p = root;
  do{
		if(p->size < size)//If too small, skip it
			p= p->succ; //If p->succ is 0, we will break out
		else if(!p->isFree) //If not free, skip it
			p= p->succ;                                        
		else if(p->size < (size + sizeof(MemEntry))){ 
			p->isFree = 0;  
			return (char *)p + sizeof(MemEntry); //return the pointer after the MemEntry struct p
			}
		else{//where am I going to put the next mementry struct. I'm also chopping up blocks
			succ = (MemEntry*)((char*)p + sizeof(MemEntry) + size); 

			succ->pattern = (int)0x55555555;
			succ -> prev = p;
			succ->succ = p-> succ;
			
			if(p->succ != 0)
				p->succ->prev = succ;
			
			p-> succ = succ;
			
			succ->size = p->size - sizeof(MemEntry) - size;
			succ->isFree = 1;
			
			p->size = size;
			p->isFree = 0;
			
			if(p == last)
				last = succ;

			return (char*)p + sizeof(MemEntry);
		}
	}while(p != 0);
  printf("Out of Space for allocation %s:%s:%d\n", file,func, line);
  return 0;
}