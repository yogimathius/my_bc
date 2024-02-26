#ifndef __MY_BC_H_
#define __MY_BC_H_

#define PROG_NAME "my_bc"

#include <stdio.h>
#include <stdlib.h>

int my_bc(const char *);
void help();

struct node {
    int data;
    struct node *next;
};

void push(struct node** top, int data);
int pop(struct node** top);
struct queue {
    struct node *stack1;
    struct node *stack2;
};

void enqueue(struct queue *q, int x);
void dequeue(struct queue *q);
void display(const struct node *top1, const struct node *top2);
void push(struct node** top, int data);
int pop(struct node** top);

int _uminus(int a, int b);
int _exp(int a, int b);
int _mul(int a, int b);
int _div(int a, int b);
int _mod(int a, int b);
int _add(int a, int b);
int _sub(int a, int b);

#endif