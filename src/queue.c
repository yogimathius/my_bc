#include <my_bc.h>

void enqueue(struct queue *q, char x){
    push_node(&q->stack1, x);
}

void push_node(struct node** top, char data){
    struct node* new = malloc(sizeof(struct node));
    if (new){
        printf("adding data: %c\n", data);
        new->data = data;
        new->next = *top;
        *top = new;
        return;
    }
    printf("Stack overflow \n");
}

int pop_node(struct node** top){
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
        printf("top1 %c\n", top1->data);
        top1 = top1->next;
    }
    while (top2){
        printf("top2 %c\n", top2->data);
        top2 = top2->next;
    }
}