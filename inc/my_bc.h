#ifndef __MY_BC_H_
#define __MY_BC_H_

#define PROG_NAME "my_bc"

#include <stdio.h>
#include <stdlib.h>

int my_bc(const char *);
void help();

struct node
{
    int data;
    struct node *next;
};
void push(struct node** top, int data);
int pop(struct node** top);
struct queue
{
    struct node *stack;
};

void enqueue(struct queue *q, int x);
void dequeue(struct queue *q);
void display(const struct node *top1, const struct node *top2);
void push(struct node** top, int data);
int pop(struct node** top);

#endif