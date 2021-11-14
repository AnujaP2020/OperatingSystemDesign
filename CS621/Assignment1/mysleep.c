/*
Anuja Gururaj Patil
NetId: yd1530

Q: 2.	Use sigaction and pause to write a function that simulates the sleep function. 
DO NOT simply write a wrapper program to call the UNIX/Linux “sleep” function.

*/


#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>  	// Header file for sleep()
#include <pthread.h> 	// for threads
#include <time.h>		// to calculate time
#include <string.h>		// string operations
#include <signal.h>		// signal headers

/*
Instructions
compile the program: 	gcc mysleep.c -o mysleep
run the program :		./mysleep <number of seconds>
*/

// handler for SIGCONT
void sigcontHandler(int signal){
    printf("Found signal %d.\n", signal);
    return;
}

// thread to send SIGCONT to paused thread
void *resumePausedThreadHandler(void *vargp){
	printf("Printing in the resumePausedThreadHandler. Sending SIGCONT now.\n");
	pthread_t pauseThread = (pthread_t) vargp;
	// send SIGCONT signal to pauseThread
	pthread_kill(pauseThread, SIGCONT);
	return NULL;
}

// thread to pause() and wait for SIGCONT using sigaction()
void *pauseThreadHandler(void *vargp){
	printf("Printing in the pauseThreadHandler.\n");

	// register sigaction handler
	struct sigaction action;
	action.sa_handler = sigcontHandler;
	sigaction(SIGCONT, &action, NULL);
	printf("Pausing now.\n");
    int ret = pause();

	return NULL;
}

int main(int argc, char *argv[]){

	if(argc <= 1){		// no arguments
		printf("Please provide number of seconds to wait for.\n");
		printf("e.g. mysleep 5 (to wait for 5 seconds)\n");
		return 1;
	}

    pthread_t pauseThread;
    pthread_t resumePausedThread;
	pthread_create(&pauseThread, NULL, pauseThreadHandler, NULL);

	int sleepSeconds = atoi(argv[1]);
	printf("Waiting %d seconds \n", sleepSeconds);

	time_t currentTime = time(0);
	time_t endTime = currentTime + sleepSeconds;

	while(time(0) < endTime){
		// do nothing, sleep
	}

	// create a new thread to send SIGCONT signal after xx (user input) seconds
	pthread_create(&resumePausedThread, NULL, resumePausedThreadHandler, pauseThread);
	pthread_join(pauseThread, NULL);
	pthread_join(resumePausedThread, NULL);

   return 0;
}
