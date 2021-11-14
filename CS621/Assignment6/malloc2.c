/*
   CS 621
   Anuja Patil
Netid: yd1530

Instructions:
# compile
$ gcc malloc2.c test.c -o test

# run
$ ./test
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "malloc2.h"
#define MAX 10

// global variables
struct Tuple arr_Tuple[MAX];
unsigned long freed_array[MAX]= {};

void print_structure(){
	printf("--------------- print_structure start ---------------\n");

	for (int i=0; i<MAX; i++){
		if (arr_Tuple[i].addri == 0){
			continue;
		}
		printf("struct array position--");
		printf("%d",i);
		printf("--address--" );
		printf("%lu",arr_Tuple[i].addri);
		printf("--size--");
		printf("%d\n",arr_Tuple[i].leni);
	}
	printf("--------------- print_structure end ---------------\n");	
}

void memcheck2(void *ptr, size_t size){
	printf("--------------- memcheck2 start ---------------\n");
	printf("memory check for pointer value--%p\n",ptr);
	printf("Pointer address in decimal-- %lu\n", (unsigned long)ptr);
	printf("--size provided for this pointer is--%lu\n",size);

	unsigned long freePtr = (unsigned long)ptr;
	bool memcheck_pass = true;
	for (int i=0; i<MAX ; i++)
	{
		if (((arr_Tuple[i].addri != 0) && (arr_Tuple[i].leni != 0)) && 
				(!((freePtr >= arr_Tuple[i].addri) && (freePtr < (arr_Tuple[i].addri + arr_Tuple[i].leni)))) && 
				(!(size <= arr_Tuple[i].leni)))
		{
			memcheck_pass = false;
		}
	}

	if (memcheck_pass){
		printf("Memory check passed.\n");
	} else {
		printf("Memory check failed.\n");
		printf("The memory address given does not lie in the range of address stored in tuple and the given size does not match with the length.\n");
	}
	printf("--------------- memcheck2 end ---------------\n");

};

void *realloc2(void *ptr, size_t size){
	printf("--------------- realloc2 start ---------------\n");

	int idx = 0;
	void *newPtr;
	unsigned long freePtr;
	freePtr = (unsigned long)ptr;
	if( ptr == NULL ) {
		newPtr = malloc2(size);
		return newPtr;
	}
	if(size == 0){
		free2(ptr);

	}
	newPtr = realloc(ptr, size);
	for (int i=0 ; i< MAX; i++)
	{
		if (freePtr == arr_Tuple[i].addri)
		{
			idx = i;
			printf("index where address is found in structure array --");
			printf("%d\n",idx);
			break;
		}
		if (freePtr >= arr_Tuple[i].addri && freePtr < (arr_Tuple[i].addri + arr_Tuple[i].leni))
		{
			idx = i;
			break;
		}
	}
	printf("New Reallocted pointer value is--%p\n",newPtr );
	printf("position--%d\n", idx);

	//now add this address to the structure array
	arr_Tuple[idx].addri = (unsigned long)newPtr;
	arr_Tuple[idx].leni = size;
	printf("--------------- realloc2 end ---------------\n");

	return newPtr;	
}

void free2(void *ptr){
	printf("--------------- free2 start ---------------\n");

	// checks for freeing meemory
	unsigned long freePtr;
	int idx = 0;
	printf("pointer value to be freed --");
	printf("%p\n",ptr );
	freePtr = (unsigned long)ptr;
	printf("address of above pointer is --");
	printf("%lu\n", freePtr);
	for (int i=0 ; i< MAX; i++)
	{
		if (freePtr == arr_Tuple[i].addri)
		{
			idx = i;
			printf("index where address is found in structure array --");
			printf("%d",idx);
			break;
		}
		if (freePtr >= arr_Tuple[i].addri && freePtr < (arr_Tuple[i].addri + arr_Tuple[i].leni))
		{
			idx = i;
			break;
		}
	}
	// this check for if given pointer is present in our structure array
	if (freePtr != arr_Tuple[idx].addri){	
		printf("The value of address is not same as address value given by malloc. We can not free memory at this address, please provide the correct address.\n");
		exit(-1);
	}
	// this check is for if user has provided some address which lies in range of addresses stored in our structure
	if (!(freePtr >= arr_Tuple[idx].addri && freePtr < (arr_Tuple[idx].addri + arr_Tuple[idx].leni)))
	{
		printf("Your specified address does not lie between memory allocated address range. Please give the correct address to free the memory.\n");
		exit(-1);
	}

	// this check for if memory is already freed at provided address
	for ( int j=0; j < MAX; j++ ) {
		if (freePtr == freed_array[j])
		{
			printf("The memory at this location is already freed.\n" );
			exit(-1);
		}
	}

	// if all conditions passed then remove tuple from the memory	
	free(ptr);
	printf("\nthe pointer--%p",ptr);
	printf("--is freed now. \n");
	freed_array[idx] = freePtr;
	printf("--------------- free2 end ---------------\n");

}

void *malloc2(size_t size){
	printf("--------------- malloc2 start ---------------\n");

	void *ptr; 
	unsigned long address;

	// check for the size and report if it is zero
	if (size == 0)
	{
		printf("Size to allocate memory can not be zero, so failed to allocate memory. Please give some other size value.\n");
		return NULL;
	}
	// call malloc to allocate memory and return tuple with address and size.
	ptr = malloc(size);
	if( ptr == NULL ) {
		printf("Error - unable to allocate required memory\n");
		return NULL;
	}		
	address = (unsigned long)ptr;
	for (int i=0; i<MAX; i++)
	{
		if (arr_Tuple[i].addri == 0){
			arr_Tuple[i].addri = address;
			arr_Tuple[i].leni = size;
			printf("struct array position--%d",i);
			printf("--address--%lu\n",arr_Tuple[i].addri);
			printf("size--%d",arr_Tuple[i].leni);
			printf("--pointr value of above address--%p\n",ptr);
			break;
		}
	}
	printf("--------------- malloc2 end ---------------\n");

	return ptr;
}
