#include "../inc/my_bc.h"

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

void push_postfix(struct queue *q, int is_operator, char my_operator, int operand){
    struct stack_element *new_node = (struct stack_element*) malloc(sizeof(struct stack_element));
    if (new_node){
        new_node->is_operator = 0;
        if (is_operator){
            new_node->is_operator = 1;
            new_node->stack_data.my_operator = my_operator;
        } else {
            new_node->stack_data.operand = operand;
        }
        new_node->next = NULL;

        struct stack_element* current = q->postfix;
        if (current == NULL) {
            q->postfix = new_node;
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

void display_postfix(const struct stack_element *top){
    printf("\n====Displaying postfix====\n");
    while (top){
        if (top->is_operator){
            printf("%c ", top->stack_data.my_operator);
        } else {
            printf("%d ", top->stack_data.operand);
        }
        top = top->next;
    }
    printf("\n");
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

void display(const struct node *top1){
    printf("\n====Displaying final_stack====\n");
    printf("top1 ");
    while (top1){
        printf("%d ", top1->data);
        top1 = top1->next;
    }
    printf("\n");
}