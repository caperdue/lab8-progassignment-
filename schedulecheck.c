#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    int schedule = sched_getscheduler(getpid());

    printf("%d\n", schedule);
    printf("%d\n", SCHED_OTHER);


    int priority = getpriority(PRIO_PROCESS, getpid());

    printf("%d\n", priority);

    // Question 7: Invalid argument
    struct sched_param schedStruct = { .sched_priority = priority};

    int setSchedule = sched_setscheduler(getpid(), SCHED_RR, &schedStruct);

    int min = sched_get_priority_min(SCHED_RR);
    int max =  sched_get_priority_max(SCHED_RR);

    printf("Min: %d, Max: %d\n", min, max);

    // Question 8: Operation not permitted

    struct sched_param schedStruct = { .sched_priority = 90};

    int setSchedule = sched_setscheduler(getpid(), SCHED_RR, &schedStruct);

    int min = sched_get_priority_min(SCHED_RR);
    int max =  sched_get_priority_max(SCHED_RR);








    printf("%d\n", setSchedule);
    printf("%s\n", strerror(errno));




}