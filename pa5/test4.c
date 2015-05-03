#include <stdio.h>
#include "malloc.h"

typedef struct s32{
	char size[32];
}S32;

typedef struct s24{
	char size[24];
}S24;

typedef struct s64{
	char size[64];
}S64;

int 
main(){
	S24 	*ptr24;
	S32 	*ptr32;
	S64 	*ptr64, *ptr64_2;
	char	*ptrC[100];
  int   *ptrI[50];
	int   i;

	//Done for testing purposes
	clearMemory();
  
  printf("\nBefore Allocation\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);
  ptr24 = (S24*)malloc(sizeof(S24));
 printf("\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);

 for(i=0; i<30;i++)
    ptrC[i] = (char*)malloc(sizeof(char));
printf("\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);

	ptr32 = (S32*)malloc(sizeof(S32));

printf("\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);
  
  for(i=30; i<60;i++)
    ptrC[i] = (char*)malloc(sizeof(char));
printf("\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);

  
	ptr64 = (S64*)malloc(sizeof(S64));
printf("\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), 5000);

  for(i=60; i<100;i++)
    ptrC[i] = (char*)malloc(sizeof(char));
  
  
  //printf("Allocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), remainingSpace());
	for(i=0; i<24;i++)
		ptr24->size[i] = '2';
	for(i=0; i<32;i++)
		ptr32->size[i] = '3';
	for(i=0; i<64;i++)
		ptr64->size[i] = '6';
  for(i=0; i<100;i++)
    *ptrC[i] = 'c';
	
  printf("\nAfter Allocation\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), remainingSpace());
  //printMemory();
  free(ptr24);
  printf("Free prt24");
  for(i=0;i<50;i++)
    free(ptrC[i]);
  printf("Free chars");
  ptr64_2 = (S64*)malloc(sizeof(S64));
  for(i=0; i<64;i++)
		ptr64->size[i] = '7';
  
  for(i=0;i<50;i++){
    ptrI[i] = (int*)malloc(sizeof(int));
    *ptrI[i] = i;
  }
  printf("\nAfter RE:Allocation\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), remainingSpace());
	//Did they properly to the front
	//printMemory();
	
	free(ptr32);
	free(ptr64);
  free(ptr64_2);
  for(i=50;i<100;i++)
    free(ptrC[i]);
	for(i=0;i<50;i++)
    free(ptrI[i]);
  
  printf("\nAfter Free\nAllocated Space: %d\nRemaining Space: %d\n", allocatedSpace(), remainingSpace());
	return 0;
}