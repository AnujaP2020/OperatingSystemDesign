/*
	netId: yd1530
	Anuja Patil

	Your assignment is to write a special version of the malloc and free library routines that checks on common heap allocation
	and usage mistakes. Your version of malloc and free will be called malloc2 and free2. You will also write one extra function,
	memcheck2, for checking if a heap allocated memory address range is safe to use. 
	A programmer will use your versions of malloc and free wherever they would use the real ones. 
	Your malloc2 and free2 will first check to see operation is safe and makes sense, and then 
	call the real malloc or free to get the job done. In addition, whenever your program needs to access heap memory, 
	they will insert a extra call to memcheck2 into their code to verify if that address range is valid. 


*/
#include <stdlib.h> // malloc, calloc, realloc, free
#include <string.h> // strcpy
#include <stdio.h> // printf

void fail(void) { printf("memory could not be allocated"); exit(EXIT_FAILURE); }

int main(void) {
    // allocate 13 bytes on the heap to hold 13 chars
    char *name = malloc2(13 * sizeof(char));
    if (name == NULL) fail();
    strcpy(name, "engineer man");

    // allocate 4 or 8 bytes on the heap to hold 2 ints, initialized to 0
    int *numbers = calloc2(2, sizeof(int));
    if (numbers == NULL) fail();
    numbers[0] = 1;
    numbers[1] = 2;

    // reallocate name to 25 bytes
    name = realloc2(name, 25 * sizeof(char));
    if (name == NULL) fail();
    strcat(name, " is the best");

    // release memory back to the operating system
    free2(name);
    free2(numbers);

    return EXIT_SUCCESS;
}