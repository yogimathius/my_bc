#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <my_bc.h>

struct stack {
    int top;
    unsigned size;
    int* array;
};

struct stack *new(unsigned size){
    struct stack *s = malloc(sizeof(struct stack));
    s->size = size;
    s->top = -1;
    s->array = malloc(s->size * sizeof(int));
    return s;
}

bool isfull(struct stack* s){
    return s->top == s->size - 1;
}

bool isempty(struct stack* s){
    return s->top == -1;
}

void push(struct stack* s, int item){
    if (isfull(s)){
        return;
    }
    s->top += 1;
    s->array[s->top] = item;
}
    
int pop(struct stack *s){
    if (isempty(s)){
        return INT_MIN;
    }
    return s->array[s->top -= 1];
}

int peek(struct stack *s){
    if (isempty(s)){
        return INT_MIN;
    }
    return s->array[s->top];
}

int nopstack=0;


void push_opstack(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK])
{
  if(nopstack>MAX_OP_STACK-1) {
    fprintf(stderr, "ERROR: Operator stack overflow\n");
    exit(EXIT_FAILURE);
  }
  opstack[nopstack++]=op;
}

struct operator_type *pop_opstack(struct operator_type *opstack[MAX_OP_STACK])
{
  if(!nopstack) {
    fprintf(stderr, "ERROR: Operator stack empty\n");
    exit(EXIT_FAILURE);
  }
  return opstack[--nopstack];
}