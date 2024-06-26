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
        struct node *curr = head;
        struct node *prev = NULL;

        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }

        Task *last = curr->task;

        if (prev!=NULL)
            delete(&head, last);
        else
            delete(&head, head->task);

        return last;
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