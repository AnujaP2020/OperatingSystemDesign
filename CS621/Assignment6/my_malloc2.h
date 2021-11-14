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

#ifndef MALLOC2_H
#define MALLOC2_H

// storage size: we can only allocate these many blocks.
// Note: this is not the size of the memory, this is just the size of the metadata: tuple(addri, leni)
#define STORAGE_SIZE 100
struct mytuple
{
	unsigned long addri;
	int leni;
};

void memcheck2(void *ptr, size_t size);
void *realloc2(void *ptr, size_t size);
void free2(void *ptr);
void *malloc2(size_t size);

#endif