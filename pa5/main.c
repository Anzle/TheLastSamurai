//#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

int
main(int argv, char** argc){
  
  int*    ptr[1000];
  int     i;
  
  /*  size of MemEntry is 24 bytes. 
  printf("Size of MemEntry %d\n", sizeof(MemEntry)); */
   printf("The end of the stack is: %d\n", ptrBound());
  clearMemory();
   //printMemory();
  for(i=0; i< 1000; i++){
    ptr[i] = (int*)malloc(sizeof(int));
    *ptr[i] = i;
   }
  printf("pointer i-1: %d\n", *ptr[i-1]);
  printf("The end of the stack is: %d\n", ptrBound());
  
  for(i = 999;i >-1;i--){
    free(ptr[i]);
  }
  printf("End: The end of the stack is: %d\n", ptrBound());
  
  return 0;
}