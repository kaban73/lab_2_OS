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

void schedule() {
    Task *task = pickTask();
    while (task != NULL) {
        run(task, task->burst);
        task = pickTask();
    }
}