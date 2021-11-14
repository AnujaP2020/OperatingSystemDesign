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

int main(){
	printf("Hello world\n");

	void * ptr, * ptr1;
	unsigned long number, number1;
	ptr = malloc(10);
	ptr1 = malloc(100);

	number = (unsigned long)ptr;
	number1 = (unsigned long)ptr1;
	if (ptr == NULL){
		printf("Memory not allocated\n");
		return 1;
	} else {
		printf("%p\t %p\t %ld\n", ptr, ptr1, (ptr1-ptr));
		printf("%ld\t %ld\t %ld\n", number, number1, (number1-number));
	}

	malloc2(10);
	return 0;
}
