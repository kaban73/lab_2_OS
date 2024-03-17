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

struct node *pr_unsort = NULL;
struct node *pr_sort = NULL;

int priority_count[10] = {0};

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    priority_count[priority]++;

    insert(&head, task);
}

Task *pickPriorityTask() {
    if (pr_unsort != NULL) {
        Task *min = pr_unsort->task;
        struct node *curr = pr_unsort->next;

        while (curr != NULL) {
            if (curr->task->priority > min->priority)
                min = curr->task;

            curr = curr->next;
        }

        delete(&pr_unsort, min);

        return min;
    } else {
        return NULL;
    }
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

void schedule_rr() {
    temp = head;
    while(head != NULL) {
        Task *task = pickTask();
        while (task != NULL) {
            if (QUANT >= task->burst) {
                run(task, task->burst);
                delete(&head, task);
            } else {
                run(task, QUANT);
                task->burst -= QUANT;
            }
            task = pickTask();
        }
        temp = head;
    }
}

void schedule() {
    pr_unsort = head;
    pr_sort = NULL;

    Task *task_pr = pickPriorityTask();
    while (task_pr != NULL) {
        insert(&pr_sort, task_pr);
        //run(task_pr, task_pr->burst);
        task_pr = pickPriorityTask();
    }

    struct node *curr = pr_sort;
    while (curr != NULL) {
        Task *task = curr->task;

        if (priority_count[task->priority] > 1) {
            struct node *pr_temp = NULL;
            while (priority_count[task->priority] != 0) {
                Task *task_pr = curr->task;
                insert(&pr_temp, task_pr);
                //run(task_pr, task_pr->burst);
                priority_count[task->priority]--;
                curr = curr->next;
            }
            head = pr_temp;
            schedule_rr();
        } else {
            run(task, task->burst);
            curr = curr->next;
        }
    }
}