#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <my_bc.h>

struct stack {
    unsigned int top;
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

bool isfull(const struct stack* s){
    return s->top == s->size - 1;
}

bool isempty(const struct stack* s){
    return s->top == (unsigned int)-1;
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

void push_opstack(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK], int *total_operations)
{
  if((*total_operations)>MAX_OP_STACK-1) {
    fprintf(stderr, "ERROR: Operator stack overflow\n");
    exit(EXIT_FAILURE);
  }
  opstack[*total_operations]=op;
  (*total_operations)++;
}

struct operator_type *pop_opstack(struct operator_type *opstack[MAX_OP_STACK], int *total_operations) {
    if(opstack[(*total_operations - 1)] == NULL) {
        printf("stack empty\n");
        return NULL;
    }
    struct operator_type *op = opstack[*total_operations-1];
    opstack[*total_operations-1] = NULL;
    (*total_operations) -= 1;
    return op;
}