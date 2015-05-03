//#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

typedef struct Large{
  int a;
  int b;
  int c;
  int d;
  int e;
} Large;


int
main(int argv, char** argc){
  
void*    ptr[1000];
  int     i, j;
  
  /*  size of MemEntry is 24 bytes. 
  printf("Size of MemEntry %d\n", sizeof(MemEntry)); */
  //printf("The end of the program space is: %p\n", ptrBound());
  clearMemory();
   //printMemory();
  for(i=0; i< 10; i++){
    if ((ptr[i] = (char*)malloc(sizeof(char))) != 0){
      char* temp = (char*)ptr[i];
      *temp = 5;
    }
    else{
	  printf("HERE\n");
      j = i;
      break;
    }
   }
  j = i;
  
  //printf("i=%d, j=%d\n", i, j);
  for(i=10; i< 20; i++){
    if ((ptr[i] = (Large*)malloc(sizeof(Large))) != 0){
      Large* temp = (Large*)ptr[i];
      temp->a = 15;
      temp->b = 15;
      temp->c = 15;
      temp->d = 15;
    }
    else{
	  printf("HERE AGAIN\n");
      j = i;
      break;
    }
   }
  j = i;
  //printf("i=%d, j=%d\n", i, j);
  
  printf("Start of our heap is: %p\n", ptr[0]);
  printf("End of our heap is: %p\n", ptr[0]+5000);
  printf("Allocation stopped at: %p\n", ptr[i-1]);
  printf("Size of Large: %lu\n", sizeof(Large));
  printf("Size of int: %lu\n", sizeof(int));
  
  //printMemory();
    
  for(i = j-1;i >-1;i--){
    free(ptr[i]);
  }

  //check for double free
  char* p = (char*)malloc(200);
  free(p);
  free(p);
  
  //check for free of unallocated memory
  int x;
  free(&x);
  
  //check for free of offset memory
  char * s = (char *) malloc(581);
  free(s+10);
  
  //regular freeing of memory
  char * another = (char *) malloc(3647);
  free(another);
  another = (char *) malloc(3647);
  free(another);
  
  printf("End of Program Reached. \n");
  return 0;
}