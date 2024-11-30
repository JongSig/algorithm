#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 9999


// calloc 함수 
void *my_calloc(size_t num, size_t size){
	// 전체 크기를 계산 
	size_t totalSize = num*size;
	
	// malloc으로 메모리 할당 
	void *ptr = malloc(totalSize);
	
	// 메모리 초기화 
	if(ptr != NULL){
		memset(ptr, 0, totalSize);
	}
	
	return ptr;
}

int main()
{
	int* iptr;
	int i,j;
	
	iptr = (int*)my_calloc(MAX, sizeof(int));
	
	if(iptr == NULL)
	{
		puts("\n Memory allocation error !");
		exit(1);
	}
	
	for(i = 2; i < MAX; i++)
	{
		if(iptr[i] == 1)
			continue;
		j = i;
		while ((j += i) <= MAX)
			iptr[j] = 1;
	}
	for(i = 2; i < MAX; i++)
		if(iptr[i] == 0)
			printf("\t%6d", i);
			
	free(iptr);
	
	return 0;
}
