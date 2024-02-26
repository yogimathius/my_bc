#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

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

