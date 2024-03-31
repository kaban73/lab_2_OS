/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE    100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    int numTasks = 0;

    in = fopen(argv[1],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);

        numTasks++;
    }

    fclose(in);

    Metrics metrics = {0, 0, 0};

    // invoke the scheduler
    schedule(&metrics);

    float turnaroundTime = (float)metrics.turnaroundTime / numTasks;
    float waitingTime = (float)metrics.waitingTime / numTasks;
    float responseTime = (float)metrics.responseTime / numTasks;

    printf("Оборотное время: %.3f\n", turnaroundTime);
    printf("Время ожидания: %.3f\n", waitingTime);
    printf("Время отклика: %.3f\n", responseTime);

    return 0;
}
