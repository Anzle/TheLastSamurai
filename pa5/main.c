//#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

int
main(int argv, char** argc){
  
  int*    ptr[1000];
  int     i, j;
  
  /*  size of MemEntry is 24 bytes. 
  printf("Size of MemEntry %d\n", sizeof(MemEntry)); */
  printf("The end of the stack is: %d\n", ptrBound());
  clearMemory();
   //printMemory();
  for(i=0; i< 1000; i++){
    if ((ptr[i] = (int*)malloc(sizeof(int))) != 0)
      *ptr[i] = i;
    else{
      j = i;
      break;
    }
   }
    printf("pointer i-1: %d\n", *ptr[i-1]);
  //printf("The end of the stack is: %d\n", ptrBound());
  
  for(i = j-1;i >-1;i--){
    free(ptr[i]);
  }

  printf("End of Program Reached. \n");
  return 0;
}