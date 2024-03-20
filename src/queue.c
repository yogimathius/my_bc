#include "../inc/my_bc.h"

void enqueue(struct queue *q, char x){
    push_node(&q->stack1, x);
}

void push_node(struct node** bottom, char data){
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node){
        new_node->data = data;
        new_node->next = NULL;

        struct node* current = *bottom;
        if (current == NULL) {
            *bottom = new_node;
        } else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
        return;
    }
    printf("Stack overflow \n");
}

void push_to_bottom(struct node** bottom, char data){
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node){
        new_node->data = data;
        new_node->next = *bottom;
        *bottom = new_node;
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
    printf("\n====Displaying stack1 and stack2====\n");
    printf("top1 ");
    while (top1){
        printf("%c ", top1->data);
        top1 = top1->next;
    }
    printf("\ntop2 ");
    while (top2){
        printf("%c ", top2->data);
        top2 = top2->next;
    }
    printf("\n");
}