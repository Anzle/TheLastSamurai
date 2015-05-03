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
	S64 	*ptr64;
	char	*ptrC[10];
	
	//Done for testing purposes
	 clearMemory();
	
	ptr24 = (S24*)malloc(sizeof(S24));
	ptr32 = (S32*)malloc(sizeof(S32));
	ptr64 = (S64*)malloc(sizeof(S64));
	int i;
	for(i=0; i<24;i++)
		ptr24->size[i] = '2';
	for(i=0; i<32;i++)
		ptr32->size[i] = '3';
	for(i=0; i<64;i++)
		ptr64->size[i] = '6';
	for(i=0;i<10;i++){
		ptrC[i] = (char*)malloc(sizeof(char));
		if(!ptrC[i])
			break;
		*ptrC[i] = 'C';
	}
	
	//Did they allocate to the front
	printMemory();
	
	free(ptr24);
	free(ptr32);
	free(ptr64);
	
	return 0;
}