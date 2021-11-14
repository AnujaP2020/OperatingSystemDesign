/*

Author: Anuja Patil, yd1530

** How to run and test **

Compile and run the program in one terminal. You can keep entering user input and
pressing 'Ctrl-C' from this terminal to send SIGINT to our process
$ gcc sig.c -o sig
$ ./sig 

From second terminal, get the PID of the `sig` process and send SIGTERM and SIGTSTM signals
to the `sig` process
$ ps -eaf | grep -i sig
$ kill -s SIGTSTP 7360
$ kill -s SIGTERM 7360


** Program requirements **
- continuously take use input until user enters `quit` or `q` or `control-c`
- schedule SIGALARM every 10 seconds
- handler for SIGINT
- handler for SIGTERM
- handler for SIGTSTP

*/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>            // for threads


#define MAX_LIMIT 20
#define MAX_COMMAND_STORAGE 100

// global variables
char commands[MAX_COMMAND_STORAGE][MAX_LIMIT];          // storing user input
int command_counter = 0, heartbeat_counter = 0;         // number of input
struct timespec start_time_cpu, start_time_user;        // starting time for CPU and User

double calculate_user_time(){
    struct timespec end_time_user;
    clock_gettime(CLOCK_REALTIME, &end_time_user);

    long seconds_user = end_time_user.tv_sec - start_time_user.tv_sec;
    long nanoseconds_user = end_time_user.tv_nsec - start_time_user.tv_nsec;
    double time_difference_user = seconds_user + nanoseconds_user*1e-9;

    return time_difference_user;
}

double calculate_cpu_time(){
    struct timespec end_time_cpu;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time_cpu);

    long seconds_cpu = end_time_cpu.tv_sec - start_time_cpu.tv_sec;
    long nanoseconds_cpu = end_time_cpu.tv_nsec - start_time_cpu.tv_nsec;
    double time_difference_cpu = seconds_cpu + nanoseconds_cpu*1e-9;

    return time_difference_cpu;
}

void sigint_handler(int signum){
    printf("------------------------------------------------------------------------\n");
    printf("handling SIGINT\n");
    printf("Time spent by the program:\n");
    printf("User time: %f seconds\n", calculate_user_time());
    printf("CPU  time: %f seconds\n", calculate_cpu_time());
    printf("------------------------------------------------------------------------\n");
}

void sigterm_handler(int signum){
    printf("------------------------------------------------------------------------\n");    
    printf("handling SIGTERM\n");
    printf("All time spent in the program: %f seconds\n", calculate_cpu_time() + calculate_user_time());
    printf("------------------------------------------------------------------------\n");
    exit(1);
}

void sigtstp_handler(int signum){
    printf("------------------------------------------------------------------------\n");
    printf("handling SIGTSTP \nLast 10 lines of user input:");
    int input_count = command_counter;

    for (int itr = input_count-1; ((itr >= 0) && (itr >= command_counter-11)); itr--){
        printf("%s\n", commands[itr]);
    }
    printf("------------------------------------------------------------------------\n");    
}

void sigalarm_handler(int signum){
    printf("------------------------------------------------------------------------\n");    
    printf("handling SIGALARM. tic %d seconds......\n", (heartbeat_counter++ * 10));
    printf("------------------------------------------------------------------------\n");    
    alarm(10);
    signal(SIGALRM, sigalarm_handler);
}

void *myAlarmThread(void *str)
{
    sigalarm_handler(1234);         // initial call to start timer
    while(1){
        printf("Sleeping\n");
        sleep(10);
    }
    return NULL;
}

int main() 
{
    // using clock_gettime() so that we can measure CPU and user time separately
    clock_gettime(CLOCK_REALTIME, &start_time_user);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time_cpu);

    // start the alarm in a new thread
    pthread_t alarmThread;
    pthread_create(&alarmThread, NULL, myAlarmThread, NULL);

    while(1) {
        scanf("%[^\n]%*c", commands[command_counter++]);
        printf("%s\n", commands[command_counter-1]);

        // Register signal handlers
        signal(SIGINT, sigint_handler);
        signal(SIGTERM, sigterm_handler);
        signal(SIGTSTP, sigtstp_handler);
        signal(SIGALRM, sigalarm_handler);

        if ((strcasecmp (commands[command_counter-1], "quit") == 0) \
            || (strcasecmp (commands[command_counter-1], "q") == 0)){
            printf ("Quiting as requested\n");
            break;
        }
    }

    // stop the thread
    pthread_join(alarmThread, NULL);

    return 0; 
} 
