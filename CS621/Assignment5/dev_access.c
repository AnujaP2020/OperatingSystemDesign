/*
   netId: yd1530
   Anuja Patil

   Now write a little C program to access some character device files. It should be a single file called dev_access.c and its specification is as follows: 
   •	if given the command line argument "0" it opens /dev/input/mouse0 and then in an infinite loop uses the read() system call to read a single byte at a time; 
   as these bytes are read, they are printed to STDOUT as integer values, one value per line (this will only work when you run the program as root) 
   •	if given the command line argument "1" it opens /dev/urandom for reading and /dev/null for writing and then reads 10 MB of pseudorandomness, 
   dumping it to /dev/null and printing the total elapsed time taken to do this using a pair of gettimeofday() calls; you are to do this using as few read() and 
   write() calls as possible; in other words, the inital read() should be passed a count parameter of 10,000,000 and subsequent calls should be for fewer bytes as 
   appropriate; you must correctly handle the situation where read() and write() do not process as many bytes as you asked for 
   •	You must check the return value of every system call. If a system call fails, print something informative and exit. Use the man pages to learn about 
   return codes. 
   •	You must perform error checking for the command line arguments. If the number of arguments is not exactly one, if this argument is not an integer, 
   or if this integer is out of range, you must print an informative error message and exit. 
   •	Your program must compile successfully using this command line:
   gcc -O2 -Wall -Wextra -Werror dev_access.c -o dev_access
   However, if you are getting crashes you should enable debugging support and turn off the optimizer:
   gcc -g -O0 -Wall -Wextra -Werror dev_access.c -o dev_access 


*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// 10 MB = 10,485,760 Bytes
#define NUMBER_OF_BYTES 10485760
int zero_handler(){

    int fd, sz;
    char c[5];

    // loop infinite times
    while (1){
        fd = open("/dev/input/mouse0", O_RDONLY);
        if (fd < 0){
		fprintf(stderr, "cannot open device file /dev/input/mouse0\n");
            	return 1;
        }
        sz = read(fd, c, 1);
        printf("%d\n",(int) c[0]);
    }

    // close file
    close(fd);
	
    return 0;
}

int one_handler(int number_of_bytes){
    struct timeval start_time, end_time;
    int fd_read, fd_write;
    int read_size = 0, write_size = 0;
    char *c = (char *) calloc(number_of_bytes+1, sizeof(char));

    gettimeofday(&start_time, NULL);
    
    // read data
    fd_read = open("/dev/urandom", O_RDONLY);
    if (fd_read < 0){
	 fprintf(stderr, "cannot open device file /dev/urandom\n");
        return 1;
    }
    read_size = read(fd_read, c, number_of_bytes);
    c[read_size] = '\0';
    printf("Read %d bytes from /dev/urandom.\n", read_size);            

    fd_write = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_write < 0){
	 fprintf(stderr, "cannot open device file /dev/null\n");
         return 1;
    }
	  
    // write data  
    write_size = write(fd_write, c, number_of_bytes);
    printf("Wrote %d bytes to /dev/null.\n", write_size);
		
    gettimeofday(&end_time, NULL);
    long long difference_seconds = (end_time.tv_sec - start_time.tv_sec);
    long long difference_microseconds = end_time.tv_usec - start_time.tv_usec;
    printf("Time difference %lld seconds %lld microseconds.\n", difference_seconds, difference_microseconds);

    // close files
    close(fd_read);
    close(fd_write);
	
    return 0;
}

int two_handler(){

    int fd, sz;
    char *c = (char *) calloc(5, sizeof(char));

    // loop 10 times
    for (int itr=0; itr<10; itr++){
        fd = open("/dev/ticket0", O_RDONLY);
        if (fd < 0){
	     fprintf(stderr, "cannot open device file /dev/ticket0\n");
             return 1;
        }
        sz = read(fd, c, 4);
        c[sz] = '\0';
        printf("Ticket number: %d\n", sz);
        sleep(1);
    }

    // close file
    close(fd);
	
    return 0;
}

int main(int argc, char const *argv[])
{
	if (argc > 2){
	    printf("Only one argument required. Too many arguments specified.\n");
	    return 1;
	} else if (argc < 2){
	    printf("Argument  missing. Please provide one argument\n");
	    return 1;
	}
	
    printf("Selected choice: %s\n", argv[1]);
	if (strcmp(argv[1],"0") == 0){
	    zero_handler();
	}
	else if (strcmp(argv[1],"1") == 0){
	    one_handler(NUMBER_OF_BYTES);
	}
	else if (strcmp(argv[1],"2") == 0){
	    two_handler();
	}
	else {
	    printf("Invalid input. Please enter numbers 0, 1 or 2\n");
	    return 1;
	}

	return 0;
}

