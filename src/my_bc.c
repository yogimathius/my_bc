#include "../inc/my_bc.h"

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int parse(char *tokens){
    struct queue q = {
        .stack1 = NULL,
        .stack2 = NULL,
    };
    int total_operations = 0;

    while (*tokens){
        if (is_alpha(*tokens)){
            dprintf(2, "parse error\n");
            return EXIT_FAILURE;
        }
        if (is_digit_char(*tokens)) {
            int num = 0;
            while (is_digit_char(*tokens)){
                num = num * 10 + (*tokens - '0');
                tokens++;
            }
            enqueue(&q, num);
            push_postfix(&q, 0, '0', num);
            continue;
        } else if (*tokens == '+' || *tokens == '-' || *tokens == '*' || *tokens == '/' || *tokens == '%' || *tokens == '^' || *tokens == '_') {
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            if (q.operators[0] == NULL){
                push_opstack(op, q.operators, &total_operations);
            }
            else {
                while (q.operators[total_operations - 1] && q.operators[total_operations - 1]->prec > op->prec){
                    printf("shunting yard\n ");
                    printf("popped operator: %c\n", q.operators[total_operations - 1]->op);
                    struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);

                    push_node(&q.stack2, popped_operator->op);
                    push_postfix(&q, 1, popped_operator->op, 0);
                }
                push_opstack(op, q.operators, &total_operations);
            }
            char *next_token = tokens + 1;
            if (*next_token == '+' || *next_token == '-' || *next_token == '*' || *next_token == '/' || *next_token == '%' || *next_token == '^' || *next_token == '_') {
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
        } else if (*tokens == '(') {
            push_opstack(getop(*tokens), q.operators, &total_operations);
            char *next_token = tokens + 1;
            if (*next_token == ')') {
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
        } else if (*tokens == ')') {
            while (q.operators[total_operations - 1]->op != '('){   
                printf("popped operator in brackets: %c\n", q.operators[total_operations - 1]->op);
                struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
                if (popped_operator != NULL) {
                    push_node(&q.stack2, popped_operator->op);
                    push_postfix(&q, 1, popped_operator->op, 0);
                }
            }
            pop_opstack(q.operators, &total_operations);

        }
        tokens += 1;
    }
    // q.operators[total_operations - 1] && q.operators[total_operations - 1]->prec > op->prec
    int i = 0;
    while (q.operators[i] != NULL){
        struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
        if (popped_operator != NULL && popped_operator->op) {
            printf("pushing operator to stack2: %c\n", popped_operator->op);
            push_node(&q.stack2, popped_operator->op);
            push_postfix(&q, 1, popped_operator->op, 0);
        }
    }
    display(q.stack1, q.stack2);
    display_postfix(q.postfix);
    while (q.stack1 != NULL && q.stack2 != NULL) {
            struct operator_type *op = getop(pop_node(&q.stack2));
            printf("operator: %c\n", op->op);
            int lhs = pop_node(&q.stack1);
            int rhs = pop_node(&q.stack1);
            printf("lhs: %d, rhs: %d\n", lhs, rhs);
            int result = op->eval(lhs, rhs);
            printf("result calculated: %d\n", result);
            // enqueue(&q, result);
            push_node(&q.stack1, result);
            // display(q.stack1, q.stack2);
    }
    int result = q.stack1->data;
    free(q.stack1);
    return result;
}

int my_bc(char *tokens){
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    return parse(tokens);;
}
