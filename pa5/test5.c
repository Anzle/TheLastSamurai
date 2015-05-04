#include <stdio.h>
#include "malloc.h"

int 
main(){
	char	*ptrC[1000];
	int   i;

	//Done for testing purposes
	clearMemory();

  for(i=0; i<200; i++){
    if( (ptrC[i]=(char*)malloc(sizeof(char))) == 0)
        break;
    printf("%d\n", i);
  }
  printf("Malloced: %d chars\n", i);
  
  for(i = i-1; i> -1;i--)
    free(ptrC[i]);
  
  return 0;
}