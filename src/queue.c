#include <my_bc.h>

void enqueue(struct queue *q, int x) {
    push(&q->stack1, x);
}

void dequeue(struct queue *q) {
    int x;
    if (q->stack1 == NULL && q->stack2 == NULL) {
        printf("queue is empty");
        return;
    }
    if (q->stack2 == NULL) {
        while (q->stack1 != NULL) {
        x = pop(&q->stack1);
        push(&q->stack2, x);
        }
    }
    x = pop(&q->stack2);
    printf("%d\n", x);
}

void push(struct node** top, int data) {
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
        if (newnode == NULL) {
            printf("Stack overflow \n");
            return;
        }
    newnode->data = data;
    newnode->next = (*top);
    (*top) = newnode;
}

int pop(struct node** top) {
    struct node *t;
    if (*top == NULL) {
        printf("Stack underflow \n");
        return 1;
    }
    else {
        t = *top;
        int buff = t->data;
        *top = t->next;
        free(t);
        return buff;
    }
}

void display(const struct node *top1, const struct node *top2) {
    while (top1 != NULL) {
        printf("%d\n", top1->data);
        top1 = top1->next;
    }
    while (top2 != NULL) {
        printf("%d\n", top2->data);
        top2 = top2->next;
    }
}