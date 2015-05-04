

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

/* Project requres a size 5000 block in the array myblock
the threshhold is for when to allocate to teh front or rear of the list*/
#define BLOCKSIZE 5000
#define THRESH    20

/* Dynamic memory in static memory! */
static char myblock[BLOCKSIZE]; 
static MemEntry	  *__ROOT__ = (MemEntry*)myblock, *__LAST__ = (MemEntry*)myblock;

/*mymalloc only uses a finite amount of space*/
void * mymalloc(unsigned int size, char* file, int line, const char* func){
  //Statics initialized on the first call only
	static int				initialized = 0;
	void * retVal;
	//MemEntry		*p, *succ;
	
	if(!initialized){
		__ROOT__ = (MemEntry *) myblock;
		__ROOT__->prev = 0;
		__ROOT__->succ = 0;
		__ROOT__->size = BLOCKSIZE - sizeof(MemEntry);
		__ROOT__->isFree = 1;
    __ROOT__->pattern = (int)0x55555555;
		initialized = 1;
    __LAST__ = __ROOT__; //For reverse allocation
	}
	//if(size <= THRESH)
	//	retVal = backwardMalloc(size, file, line, func);
 // else
    retVal = forwardMalloc(size, file, line, func);
	
 // printf("root:last = %p:%p\n", __ROOT__, __LAST__);
/*    if (retVal)
		printf("Successfully allocated %ld blocks\n", (size+sizeof(MemEntry)));
	 */
   return retVal;
  
  
}//End myMalloc

void myfree(void * p, char* file, int line){
	MemEntry		*ptr, *pred, *succ;
	
	if((char*)p < myblock || (char*)p > myblock + BLOCKSIZE){
		printf("Error: Memory Not Allocated %s:%d\n", file, line);
		return;
	}
	ptr = (MemEntry*)((char*)p - sizeof(MemEntry));
  
  //move last if needed
  if(ptr ==  __LAST__&& ptr->prev)
    __LAST__ = ptr->prev;
  
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
    printf("%c", myblock[i]);
  printf("\n");
  
}

int remainingSpace(){
	int size = BLOCKSIZE - allocatedSpace();
  return size;
}

int allocatedSpace(){
	MemEntry  *ptr = (MemEntry*)myblock;
  unsigned int size = 0;
  do{
    if(!ptr->isFree)
      size += ptr->size;
    ptr = ptr->succ;
  }while(ptr);
  
  return size;
}

void * backwardMalloc(unsigned int size, char* file, int line, const char* func){
  MemEntry *p, *succ;
  p = __LAST__;
  

 do{
    if(p->size < size)//If too small, skip it
			p = p->prev; 
		else if(!p->isFree) //If not free, skip it
			p = p->prev;                                        
		else if(p->size < (size + sizeof(MemEntry))){ 
			p->isFree = 0;  
			return (char *)p + sizeof(MemEntry); //return the pointer after the MemEntry struct p
			}
		else{
      //Create a memory block up the tail of the list
      
      succ = (MemEntry*)((char*)p + (p->size - (sizeof(MemEntry) + size))); 
      
      succ->pattern = (int)0x55555555;
      succ-> prev = p;
			succ->succ = p-> succ;
			
      if(p->succ != 0)
				p->succ->prev = succ;
			
      p->succ = succ;
			
      succ->size = sizeof(MemEntry) + size;
			succ->isFree = 0;
			
      p->size = p->size - succ->size;
			p->isFree = 1;

      if( p == __LAST__)
        __LAST__ = succ;
    
      return (char*)succ + sizeof(MemEntry);
		}
	} while(p != 0 && ((char*)p > myblock || (char*)p < myblock + BLOCKSIZE));
  
  printf("Out of Space for allocation %s:%s:%d\n", file, func, line);
  return 0;
}

void * forwardMalloc(unsigned int size, char* file, int line, const char* func){
  MemEntry *p, *succ;
  p = __ROOT__;
  do{
		if(p->size < size)//If too small, skip it
			p= p->succ; 
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
			
      //printf("Address of p:last %p:%p\n", p, __LAST__);
			if(p == __LAST__){
				__LAST__ = p->succ;
      }
      //printf("Address of p:last %p:%p\n", p, __LAST__);
			return (char*)p + sizeof(MemEntry);
		}
	}while(p != 0);
  
  printf("Out of Space for allocation %s:%s:%d\n", file,func, line);
  return 0;
}