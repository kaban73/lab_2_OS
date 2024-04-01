//
// Created by ivankabanov on 16.03.24.
//
#include "stdio.h"
#include "stdlib.h"
#include "task.h"
#include "list.h"

#define QUANT 10

struct node *head = NULL;
struct node *temp = NULL;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    insert(&head, task);
}

Task *pickTask() {
    if (temp != NULL) {
        Task *task = temp->task;
        temp = temp->next;
        return task;
    } else {
        return NULL;
    }
}

void schedule(Metrics *metrics) {
    temp = head;
    int fl_rt = 0;
    int fl_tr = 0;
    int temp_turnaround = 0;
    while(head != NULL) {
        Task *task = pickTask();
        int currentTime = 0;
        while (task != NULL) {
            if (fl_rt == 0)
                metrics->responseTime += currentTime;
            if (QUANT >= task->burst) {
                run(task, task->burst);
                delete(&head, task);

                currentTime += task->burst;
                metrics->turnaroundTime += currentTime;
                metrics->waitingTime += currentTime - task->burst;
            } else {
                run(task, QUANT);
                task->burst -= QUANT;

                currentTime += QUANT;
                metrics->turnaroundTime += currentTime;
                metrics->waitingTime += currentTime - QUANT;
            }
            task = pickTask();
        }

        printf("\nWaiting time: %d\n", metrics->waitingTime);

        temp = head;
        if (fl_tr == 0) {
            temp_turnaround = metrics->turnaroundTime;
            fl_tr = 1;
        }
        fl_rt = 1;
    }
    metrics->turnaroundTime += temp_turnaround;
}