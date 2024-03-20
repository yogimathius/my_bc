#include "../inc/my_bc.h"

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int parse(char *tokens){
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
            char *num = (char *)malloc(sizeof(char) * 10);
            int i = 0;
            num[i] = *tokens;
            char *temp_ptr;
            temp_ptr = tokens;
            while (*temp_ptr++ && *temp_ptr >= '0' && *temp_ptr <= '9'){
                i += 1;
                num[i] = *temp_ptr;
            }
            tokens += i;
            enqueue(&q, atoi(num));
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
            push_node(&q.stack2, popped_operator->op);
        }
    }
    // display(q.stack1, q.stack2);
    while (q.stack1 != NULL && q.stack2 != NULL) {
            struct operator_type *op = getop(pop_node(&q.stack2));
            int lhs = pop_node(&q.stack1);
            int rhs = pop_node(&q.stack1);
            // printf("lhs: %c, rhs: %c\n", lhs, rhs);

            
            int result = op->eval(lhs, rhs);
            // printf("result calculated: %d\n", result);
            // enqueue(&q, result);
            push_to_bottom(&q.stack1, result + '0');
            // display(q.stack1, q.stack2);
    }
    int result = q.stack1->data;
    free(q.stack1);
    return result - '0';
}

int my_bc(char *tokens){
    return parse(tokens);;
}
