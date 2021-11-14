/*
Anuja Gururj Patil
NetId: yd1530

Q. Simulate the UNIX utility time that shows the time taken by a program. Your command line syntax should be as follows: 
(mytime command). This program should invoke a program which gets the CPU time, forks a child to run command and when 
the child returns gets the CPU time again and prints the difference between the two times. You do not need to re-invent 
the concept of time. You can use a built-in Unix/Linux timer utility to keep the time.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 	        // for threads
#include <time.h>				// to calculate time

  /* Instructions
  compile the program: 	gcc mytime.c -o mytime
  run the program :		./mytime <command> 
  */

void *myTimeThread(void *str)
{
	system(str);
	return NULL;
}

int main (int argc, char *argv[])
{

	if(argc <= 1)
	{		// no arguments
		printf("Please provide any command to execute.\n");
		printf("e.g. mytime pwd (command to display current directory) \n");
		return 1;
	}
	clock_t timeBeforeThread = clock();
	printf("Time before thread %ld\n", timeBeforeThread);
	pthread_t myThread;
	// print command line input parameter
	char *command = argv[1];
	printf("Executing  %s command \n", command);
	// pass arguments to the method
	pthread_create(&myThread, NULL, myTimeThread, (void*) command);
	pthread_join(myThread, NULL);
	clock_t timeAfterThread = clock();
	printf("Time after thread %ld\n", timeAfterThread);
	printf("----------------------\n");
	printf("Time difference %f seconds. \n", (double)(timeAfterThread - timeBeforeThread)/CLOCKS_PER_SEC);
	printf("----------------------\n");
	return 0;
}
