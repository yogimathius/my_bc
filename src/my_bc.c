#include "../inc/my_bc.h"

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int parse(const char *tokens){
    struct queue q = {
        .stack1 = NULL,
        .stack2 = NULL,
        .operators = {}
    };
    int total_operations = 0;
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    while (*tokens){
        if (*tokens >= '0' && *tokens <= '9') {
            // while (*tokens++ >= '0' && *tokens <= '9') {
                
            // }
            enqueue(&q, *tokens);
        } else if (*tokens == '+' || *tokens == '-' || *tokens == '*' || *tokens == '/') {
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            if (q.operators[0] == NULL){
                push_node(&q.stack2, *tokens);
            }
            else {
                while (q.operators[total_operations - 1] && q.operators[total_operations - 1]->prec > op->prec){
                    struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);

                    push_node(&q.stack2, popped_operator->op);
                }
                push_opstack(op, q.operators, &total_operations);
            }
        } else if (*tokens == '(') {
            push_opstack(getop(*tokens), q.operators, &total_operations);
        } else if (*tokens == ')') {
            while (q.operators[total_operations - 1]->op != '('){
                struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
                if (popped_operator != NULL) {
                    push_node(&q.stack2, popped_operator->op);
                }
            }
            pop_opstack(q.operators, &total_operations);

        }
        tokens += 1;
    }
    while (q.operators[0] != NULL){
        struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
        if (popped_operator != NULL) {
            enqueue(&q, popped_operator->op);
        }
    }
    display(q.stack1, q.stack2);
    while (q.stack1 != NULL && q.stack2 != NULL) {
            struct operator_type *op = getop(pop_node(&q.stack2));
            char lhs_char = pop_node(&q.stack1);
            char rhs_char = pop_node(&q.stack1);
            printf("lhs_char: %c, rhs_char: %c\n", lhs_char, rhs_char);

            int lhs = (int)(lhs_char) - '0';
            int rhs = (int)(rhs_char) - '0';
            
            int result = op->eval(lhs, rhs);
            printf("result calculated: %d\n", result);
            // enqueue(&q, result);
            push_to_bottom(&q.stack1, result + '0');
            display(q.stack1, q.stack2);
    }
    int result = q.stack1->data;
    free(q.stack1);
    return result - '0';
}

int my_bc(const char *tokens){
    return parse(tokens);;
}
