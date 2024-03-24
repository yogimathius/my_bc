#ifndef __MY_BC_H_
#define __MY_BC_H_

#define PROG_NAME "my_bc"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_OP_STACK 100

int my_bc(char *);
void help();

struct node {
    int data;
    struct node *next;
};

struct stack_element {
    int is_operator;
    union {
        int operand;
        char my_operator;
    } stack_data;
    struct stack_element *next;
};

void push_node(struct node** bottom, char data);

char pop_node(struct node** top);
struct queue {
    struct node *stack1;
    struct node *stack2;
    struct stack_element *postfix;
    struct operator_type *operators[MAX_OP_STACK];
};



void enqueue(struct queue *q, char data);
void display(const struct node *top1, const struct node *top2);

bool is_digit_char(char c);
bool is_operator(char c);
bool is_alpha(char c);

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
  int (*eval)(int a1, int a2);
};

struct operator_type *getop(char ch);

struct operator_type *pop_opstack(struct operator_type *opstack[MAX_OP_STACK], int *total_operations);
void push_opstack(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK], int *total_operations);
void push_postfix(struct queue *q, int is_operator, char my_operator, int operand);
void display_postfix(const struct stack_element *top);

#endif