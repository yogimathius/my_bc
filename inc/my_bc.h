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

enum {ASSOC_NONE=0, ASSOC_LEFT, ASSOC_RIGHT};

struct operator_type {
  char op;
  int prec;
  int assoc;
  int unary;
  float (*eval)(float a1, float a2);
} operators[]={
  {'_', 10, ASSOC_RIGHT, 1, _uminus},
  {'^', 9,  ASSOC_RIGHT, 0, _exp},
  {'*', 8,  ASSOC_LEFT,  0, _mul},
  {'/', 8,  ASSOC_LEFT,  0, _div},
  {'%', 8,  ASSOC_LEFT,  0, _mod},
  {'+', 5,  ASSOC_LEFT,  0, _add},
  {'-', 5,  ASSOC_LEFT,  0, _sub},
  {'(', 0,  ASSOC_NONE,  0, NULL},
  {')', 0,  ASSOC_NONE,  0, NULL}
};

#endif