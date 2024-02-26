#include <my_bc.h>

void enqueue(struct queue *q, int x){
    push(&q->stack1, x);
}

void dequeue(struct queue *q){
    int x;
    if (q->stack1 == NULL && q->stack2 == NULL){
        printf("queue is empty");
        return;
    }
    if (q->stack2 == NULL) {
        while (q->stack1) {
            x = pop(&q->stack1);
            push(&q->stack2, x);
        }
    }
    x = pop(&q->stack2);
    printf("%d\n", x);
}

void push(struct node** top, int data){
    struct node* new = malloc(sizeof(struct node));
    if (new){
        new->data = data;
        new->next = *top;
        *top = new;
        return;
    }
    printf("Stack overflow \n");
}

int pop(struct node** top){
    struct node *t;
    if (*top){
        t = *top;
        int data = t->data;
        *top = t->next;
        free(t);
        return data;
    }
    printf("Stack underflow \n");
    return 1;
}

void display(const struct node *top1, const struct node *top2){
    while (top1){
        printf("%d\n", top1->data);
        top1 = top1->next;
    }
    while (top2){
        printf("%d\n", top2->data);
        top2 = top2->next;
    }
}