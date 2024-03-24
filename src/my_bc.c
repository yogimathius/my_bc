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
        // If the incoming symbols is an operand, print it..
        if (is_alpha(*tokens)){
            dprintf(2, "parse error\n");
            return EXIT_FAILURE;
        }
        if (is_operand(*tokens)) {
            int num = 0;
            while (is_operand(*tokens)){
                num = num * 10 + (*tokens - '0');
                tokens++;
            }
            // enqueue(&q, num);
            push_postfix(&q, 0, '0', num);
            continue;
        } else if (is_operator(*tokens)) {
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            // If the incoming symbol is an operator and has either higher precedence than the operator on the top of the stack, or has the same precedence as the operator on the top of the stack and is right associative, or if the top of the stack is "(" (a floor) -- push it on the stack.
            if (should_push_operator(op, q.operators, total_operations)){
                printf("pushing operator to stack empty: %c\n", op->op);
                push_opstack(op, q.operators, &total_operations);
            }
            else {
                // If the incoming symbol is an operator and has either lower precedence than the operator on the top of the stack, or has the same precedence as the operator on the top of the stack and is left associative -- continue to pop the stack until this is not true. Then, push the incoming operator.
                while (should_shunt(op, q.operators, total_operations)){
                    printf("shunting yard\n ");
                    printf("popped operator: %c\n", q.operators[total_operations - 1]->op);
                    struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);

                    // push_node(&q.stack2, popped_operator->op);
                    push_postfix(&q, 1, popped_operator->op, 0);
                }
                push_opstack(op, q.operators, &total_operations);
            }
            char *next_token = tokens + 1;
            if (is_operator(*next_token)){
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
        // If the incoming symbol is a left parenthesis, push it on the stack.
        } else if (*tokens == '(') {
            push_opstack(getop(*tokens), q.operators, &total_operations);
            char *next_token = tokens + 1;
            if (*next_token == ')') {
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
        // If the incoming symbol is a right parenthesis: discard the right     parenthesis, pop and print the stack symbols until you see a left parenthesis. Pop the left parenthesis and discard it.
        } else if (*tokens == ')') {
            while (q.operators[total_operations - 1]->op != '('){   
                printf("popped operator in brackets: %c\n", q.operators[total_operations - 1]->op);
                struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
                if (popped_operator != NULL) {
                    // push_node(&q.stack2, popped_operator->op);
                    push_postfix(&q, 1, popped_operator->op, 0);
                }
            }
            pop_opstack(q.operators, &total_operations);

        }
        tokens += 1;
    }
    int i = 0;
    while (q.operators[i] != NULL){
        struct operator_type *popped_operator = pop_opstack(q.operators, &total_operations);
        if (popped_operator != NULL && popped_operator->op) {
            printf("pushing operator to stack2: %c\n", popped_operator->op);
            // push_node(&q.stack2, popped_operator->op);
            push_postfix(&q, 1, popped_operator->op, 0);
        }
    }
    display(q.stack1);
    display_postfix(q.postfix);

    while (q.postfix != NULL){
        struct stack_element *current = q.postfix;
        display(q.stack1);
        if (current->is_operator){
            struct operator_type *op = getop(current->stack_data.my_operator);
            printf("operator: %c\n", op->op);
            int rhs = pop_node(&q.stack1);
            int lhs = pop_node(&q.stack1);
            printf("lhs: %d, rhs: %d\n", lhs, rhs);
            int result = op->eval(lhs, rhs);
            printf("result calculated: %d\n", result);
            push_node(&q.stack1, result);
        } else {
            printf("operand: %d\n", current->stack_data.operand);
            push_node(&q.stack1, current->stack_data.operand);
        }
        q.postfix = q.postfix->next;
    }

    // while (q.stack1 != NULL && q.stack2 != NULL) {
    //         struct operator_type *op = getop(pop_node(&q.stack2));
    //         printf("operator: %c\n", op->op);
    //         int lhs = pop_node(&q.stack1);
    //         int rhs = pop_node(&q.stack1);
    //         printf("lhs: %d, rhs: %d\n", lhs, rhs);
    //         int result = op->eval(lhs, rhs);
    //         printf("result calculated: %d\n", result);
    //         // enqueue(&q, result);
    //         push_node(&q.stack1, result);
    //         // display(q.stack1, q.stack2);
    // }
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
