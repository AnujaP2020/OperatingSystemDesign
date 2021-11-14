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
#define MALLOC2



// tuple structure declaration
struct Tuple{
	unsigned long addri;
	int leni;
};

void memcheck2(void *ptr, size_t size);
void *realloc2(void *ptr, size_t size);
void free2(void *ptr);
void *malloc2(size_t size);
void print_structure();

#endif
