#include <my_bc.h>

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
    // struct stack operators = Stack.new();
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    while (*tokens){
        if (*tokens >= '0' && *tokens <= '9') {
            dprintf(1, "\n======number======: %c\n", *tokens);
            enqueue(&q, *tokens);
        } else if (*tokens == '+' || *tokens == '-' || *tokens == '*' || *tokens == '/') {
            dprintf(1, "\n======operator======: %c\n", *tokens);
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            if (q.operators[0] == NULL){
                printf("operators null, adding: %c\n", op->op);
                push_opstack(op, q.operators, &total_operations);
            }
            else {
                printf("checking precedence: %c\n", q.operators[total_operations - 1]->op);
                printf("checking precedence: %c\n", op->op);
                while (q.operators[total_operations - 1] && q.operators[total_operations - 1]->prec > op->prec){
                    printf("precedent higher, enqueuing: %c\n", q.operators[total_operations - 1]->op);
                    enqueue(&q, pop_opstack(q.operators, &total_operations)->op);
                }
                push_opstack(op, q.operators, &total_operations);
            }
        } else if (*tokens == '(') {
            dprintf(1, "\n======left bracket======: %c\n", *tokens);
            push_opstack(getop(*tokens), q.operators, &total_operations);
        } else if (*tokens == ')') {
            dprintf(1, "\n======right bracket======: %c\n", *tokens);
            while (q.operators[total_operations - 1]->op != '('){
                struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
                if (popped_operator != NULL) {
                    enqueue(&q,popped_operator->op);
                }
            }
            pop_opstack(q.operators, &total_operations);
            if (q.operators[0] == NULL) {
                printf("successfully popped all operators\n");
            }

        }
        tokens += 1;
    }
    // 13. While there are operators on the stack, pop them to the queue
    while (q.operators[0] != NULL){
        printf("test %c\n", q.operators[0]->op);
        struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
        if (popped_operator != NULL) {
            enqueue(&q, popped_operator->op);
        }
    }
    display(q.stack1, q.stack2);
    return EXIT_SUCCESS;
}

int my_bc(const char *tokens){
    return parse(tokens);;
}
