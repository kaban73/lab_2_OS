//
// Created by ivankabanov on 16.03.24.
//
#include "stdio.h"
#include "stdlib.h"
#include "task.h"
#include "list.h"

struct node *head = NULL;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    insert(&head, task);
}

Task *pickTask() {
    if (head != NULL) {
        Task *min = head->task;
        struct node *curr = head->next;

        while (curr != NULL) {
            if (curr->task->burst < min->burst)
                min = curr->task;

            curr = curr->next;
        }

        delete(&head, min);

        return min;
    } else {
        return NULL;
    }
}

void schedule(Metrics *metrics) {
    Task *task = pickTask();
    int currentTime = 0;

    while (task != NULL) {
        metrics->responseTime += currentTime;

        run(task, task->burst);

        currentTime += task->burst;
        metrics->turnaroundTime += currentTime;

        task = pickTask();
    }
}