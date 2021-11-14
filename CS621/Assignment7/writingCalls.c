/*

Author: Anuja Patil, yd1530

Instructions:
# compile
$ gcc writingCalls.c -o call

# run
$ ./call
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // to calculate time
#include <fcntl.h>
#include <unistd.h>

#define MAX 128
#define Byte 1024

long calculate_writing_time_write(struct timeval t0, struct timeval t1, int size){
	
	FILE *fp;
	int sz, count_of_write = 0;
	// we will get the current time here before writing to files
	gettimeofday(&t0, 0);

	// loop here to write for 10 times 
	for (int k = 0; k < 10; k++){

		char string[128*1024];
		char filename[100];

		snprintf(filename, 100, "/home/anuja/Templates/myFiles/writeFiles_size_%d_%d.txt",size,k+1);
		int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			fprintf(stderr, "problem opening file\n");
			exit(1);
		}

		// loop here to append to the file and reach the maximum given size of file 
		for (int j=0; j< (MAX*Byte)/size; j++){
			sz = write(fd,string,size);
			// recording write operation count
			count_of_write++;
		}
		close(fd);
	}
	printf("Number of write operations: %d and elapsed time is :",count_of_write );

	// this will be our final time after writing in files
	gettimeofday(&t1, 0);
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;

	return elapsed;

}

long calculate_writing_time_fwrite(struct timeval t0, struct timeval t1, int size){

    FILE *fp;
    int count_of_fwrite = 0;
	// we will get the current time here before writing to files
	gettimeofday(&t0, 0);

	// loop here to write for 10 times 
	for (int k = 0; k < 10; k++){

		char string[128*1024];
		char filename[100];

		snprintf(filename, 100, "/home/anuja/Templates/myFiles/fwriteFiles_size_%d_%d.txt",size,k+1);
		FILE* fp = fopen(filename, "a+");
		if (fp == NULL) {
	        fprintf(stderr, "problem opening file\n");
	        exit(1);
	    }

		// loop here to append to the file and reach the maximum given size of file 
		for (int j=0; j< (MAX*Byte)/size; j++){
			fwrite (string, 1, size, fp);
			// recording fwrite operation count
			count_of_fwrite++;
		}
		fclose(fp);
	}
	printf("Number of fwrite operations: %d and elapsed time is :",count_of_fwrite );

	// this will be our final time after writing in files
	gettimeofday(&t1, 0);
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;

	return elapsed;

}


int main()
{

	// find the time for write system call first
	struct timeval t0, t1;
	int size;
	int array_size = 6; // as per given program
	// declaration of array to store given sizes
	int array[array_size] = {2, 16, 128, 1024, 8192, 65536};
	long write_elapsed_array[array_size];
	long fwrite_elapsed_array[array_size];

	printf("**************elapsed time for each given size using write system call************\n");

	for (int i=0; i< array_size; i++){

		// call function here to get the elapsed time and writing to the files
		printf("For size_%d\n",array[i]); 
		write_elapsed_array[i] = calculate_writing_time_write(t0, t1, array[i]);
		printf("%ld\n",write_elapsed_array[i]);
	}

	printf("**************elapsed time for each given size using fwrite function call***********\n");
	// this loop for fwrite function
	for (int i=0; i< array_size; i++){

		// call function here to get the elapsed time and writing to the files
		printf("For size_%d\n",array[i]); 
		fwrite_elapsed_array[i] = calculate_writing_time_fwrite(t0, t1, array[i]);
		printf("%ld\n",fwrite_elapsed_array[i]);
	}














	return 0;
}

