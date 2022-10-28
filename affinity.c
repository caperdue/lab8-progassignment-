#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NLOOPS 200000000
#define NUM_PROCS 8

int main(int argc, char *argv[])
{
    cpu_set_t set;
    int joinedCPU = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s {0|1}\n", argv[0]);
        exit(1);
    }

    
    CPU_ZERO(&set);
    CPU_SET(joinedCPU, &set);

    printf("%d\n", CPU_COUNT(&set));

    if (atoi(argv[1]) != 0) {
        // Set the affinity
        size_t cpusetsize = sizeof(cpu_set_t);
        int val = sched_setaffinity(getpid(), cpusetsize, &set);
        printf("%d\n", val);
    }

    pid_t pid;
    for (int i = 0; i < NUM_PROCS - 1; i++) {
        if ((pid = fork()) < 0) {
            perror("Problem forking");

            exit(1);
        } else if (!pid) {
            break;
        }
    }

    long sum = 0;
    for (long j = 0; j < NLOOPS; j++) {
        sum += j;  // meaningless work to keep the CPU busy
   //     printf("\r%lu ", sum);
    }
    printf("\n");

    return 0;
}
