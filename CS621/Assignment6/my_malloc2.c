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
#include "abhi_malloc2.h"

// to store address and lenghts
struct mytuple tuple_array[STORAGE_SIZE];
// to store how many address blocks have been alloacated.
int global_counter = 0;

void memcheck2(void *ptr, size_t size){

}

void *realloc2(void *ptr, size_t size){

	return NULL;
}

void free2(void *ptr){
	unsigned long address = (unsigned int)ptr;

	// make sure we have allocated that memory
	for(int itr=0; itr<STORAGE_SIZE; itr++){
		if (tuple_array[itr].addri == address){
			free(ptr);

			// mark it as 0, so that we can store new address here when we malloc2()
			tuple_array[itr].addri = 0;
			tuple_array[itr].leni = 0;

			// decrease so that we know how many metadata blocks are available
			global_counter--;

			// todo: handle case 2 (not the first byte) and 3 (double free)
			return;
		}
	}
	printf("Memory\n");

}

void *malloc2(size_t size){
	void * ptr;
	if (size == 0){
		printf("Allocating memory for zero size is futile. Returning.\n");
		return NULL;
	}

	if(global_counter >= STORAGE_SIZE){
		printf("Our metadata storage is full, please free some memory before allocating.\n");
		return NULL;
	}

	ptr = malloc(size);
	if (ptr == NULL){
		return ptr;
	}

	// find first metadata block available to store addri and leni and write to it
	for (int itr=0; itr<STORAGE_SIZE; itr++){
		if (tuple_array[itr].leni != 0){
			continue;
		}
		tuple_array[itr].addri = (unsigned long)ptr;
		tuple_array[itr].leni = size;
		global_counter++;
		break;
	}

	return ptr;
}





