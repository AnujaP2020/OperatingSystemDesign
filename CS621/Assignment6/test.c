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
#include "malloc2.h"

int main(){
	void *malloc_ptr1, *malloc_ptr2, *malloc_ptr3;
	//unsigned long ptr;
	malloc_ptr1 = malloc2(140);
	malloc_ptr2 = malloc2(18);
	malloc_ptr3 = malloc2(90);
	print_structure();

	free2(malloc_ptr3);
	print_structure();

	realloc2(malloc_ptr1,100);
	print_structure();

	// memcheck success case
	memcheck2(malloc_ptr2,10);
	// memcheck failure case
	memcheck2(malloc_ptr2,1000);

	print_structure();
	return 0;
}
