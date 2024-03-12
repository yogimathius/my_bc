#include <my_bc.h>

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int parse(const char *tokens){
    struct queue q = {
        .stack1 = NULL,
        .stack2 = NULL
    };
    int total_operations = 0;
    // struct stack operators = Stack.new();
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    while (*tokens){
        if (*tokens >= '0' && *tokens <= '9') {
            dprintf(1, "number: %c\n", *tokens);
            enqueue(&q, *tokens - 48);
        } else if (*tokens == '+' || *tokens == '-' || *tokens == '*' || *tokens == '/') {
            dprintf(1, "operator: %c\n", *tokens);
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            if (q.operators[0] == NULL){
                push_opstack(op, q.operators, &total_operations);
            }
            else {
                int i = 0;
                while (q.operators[i] && q.operators[i]->prec > op->prec){
                    enqueue(&q, pop_opstack(q.operators, &total_operations)->op);
                }
                push_opstack(op, q.operators, &total_operations);
            }
        } else if (*tokens == '(') {
            dprintf(1, "left bracket: %c\n", *tokens);
            push_opstack(getop(*tokens), q.operators, &total_operations);
        } else if (*tokens == ')') {
            dprintf(1, "right bracket: %c\n", *tokens);
            while (q.operators[total_operations - 1]->op != '('){
                printf("test\n");
                struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
                if (popped_operator != NULL) {
                    printf("enqueing\n");
                    enqueue(&q,popped_operator->op);
                }
            }
            printf("popping %c\n", q.operators[total_operations - 1]->op);
            pop_opstack(q.operators, &total_operations);
            if (q.operators[0] == NULL) {
                printf("success\n");
            }

        }
        tokens += 1;
    }
    // 13. While there are operators on the stack, pop them to the queue
    // while (q.operators[0] != NULL){
    //     printf("test %c\n", q.operators[0]->op);
    //     struct operator_type *popped_operator = pop_opstack(q.operators);
    //     if (popped_operator != NULL) {
    //         enqueue(&q, popped_operator->op);
    //     }
    // }
    // display(q.stack1, q.stack2);
    return EXIT_SUCCESS;
}

int my_bc(const char *tokens){
    return parse(tokens);;
}
