#include <my_bc.h>

void enqueue(struct queue *q, char x){
    push_node(&q->stack1, x);
}

void push_node(struct node** top, int data){
    struct node* new = malloc(sizeof(struct node));
    if (new){
        new->data = data;
        new->next = NULL;

        struct node* current = *bottom;
        if (current == NULL) {
            *bottom = new;
        } else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new;
        }
        return;
    }
    printf("Stack overflow \n");
}

void push_to_bottom(struct node** bottom, char data){
    struct node* new = malloc(sizeof(struct node));
    if (new){
        new->data = data;
        new->next = *bottom;
        *bottom = new;
        return;
    }
    printf("Stack overflow \n");
}


char pop_node(struct node** top){
    struct node *t;
    if (*top){
        t = *top;
        char data = t->data;
        *top = t->next;
        free(t);
        return data;
    }
    printf("Stack underflow \n");
    return '0';
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