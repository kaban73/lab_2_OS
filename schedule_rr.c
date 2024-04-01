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
    while(head != NULL) {
        Task *task = pickTask();
        int currentTime = 0;
        while (task != NULL) {
            if (QUANT >= task->burst) {

                metrics->responseTime += currentTime;

                metrics->waitingTime += currentTime - task->burst;

                run(task, task->burst);

                currentTime += task->burst;
                metrics->turnaroundTime += currentTime;

                delete(&head, task);
            } else {
                metrics->responseTime += currentTime;

                metrics->waitingTime += currentTime - QUANT;

                run(task, QUANT);
                task->burst -= QUANT;

                currentTime += QUANT;
                metrics->turnaroundTime += currentTime;
            }
            task = pickTask();
        }
        temp = head;
    }
}