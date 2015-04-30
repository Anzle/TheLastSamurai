#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

int
main(int argv, char** argc){
  
  int*    ptr[1000];
  int     i;
  
  /*  size of MemEntry is 24 bytes. 
  printf("Size of MemEntry %d\n", sizeof(MemEntry)); */
  
 /*  for(i=0; i< 999; i++){
    ptr[i] = (int*)mymalloc(sizeof(int));
    *ptr[i] = i;
  } */
  
  
  /* printf("Middle: The end of the stack is: %d\n", ptrBound());
  
  for(;i < 2000;i++){
    ptr[i] = (int*)mymalloc(sizeof(int));
    *ptr[i] = i;
  }
  printf("End: The end of the stack is: %d\n", ptrBound()); */
  
  return 0;
}