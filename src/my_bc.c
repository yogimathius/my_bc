#include "../inc/my_bc.h"

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

void reverse_polish(struct queue *q){
    while (q->postfix != NULL){
        struct stack_element *current = q->postfix;
        if (current->is_operator){
            struct operator_type *op = getop(current->stack_data.my_operator);
            int rhs = pop_node(&q->final_stack);
            int lhs = pop_node(&q->final_stack);
            int result = op->eval(lhs, rhs);
            push_node(&q->final_stack, result);
        } else {
            push_node(&q->final_stack, current->stack_data.operand);
        }
        q->postfix = q->postfix->next;
    }
}

int parse(char *tokens, struct queue *q, int *total_operations){
    while (*tokens){
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
            push_postfix(q, 0, '0', num);
            continue;
        } else if (is_operator(*tokens)) {
            struct operator_type *op = getop(*tokens);
            if (op == NULL){
                dprintf(2, "ERROR: operator not found\n");
                return EXIT_FAILURE;
            }
            char *next_token = tokens + 1;
            if (is_operator(*next_token)){
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
            if (should_push_operator(op, q->operators, *total_operations)){
                push_opstack(op, q->operators, total_operations);
            }
            else {
                while (should_shunt(op, q->operators, *total_operations)){
                    push_postfix(q, 1, pop_opstack(q->operators, total_operations)->op, 0);
                }
                push_opstack(op, q->operators, total_operations);
            }
        } else if (*tokens == '(') {
            char *next_token = tokens + 1;
            if (*next_token == ')') {
                dprintf(2, "parse error\n");
                return EXIT_FAILURE;
            }
            push_opstack(getop(*tokens), q->operators, total_operations);
        } else if (*tokens == ')') {
            while (q->operators[*total_operations - 1]->op != '('){   
                push_postfix(q, 1, pop_opstack(q->operators, total_operations)->op, 0);
            }
            pop_opstack(q->operators, total_operations);

        }
        tokens += 1;
    }
    return EXIT_SUCCESS;
}

int calculate(char *tokens){
    struct queue q = {
        .final_stack = NULL,
    };
    int total_operations = 0;
    
    if (parse(tokens, &q, &total_operations) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    while (q.operators[0] != NULL){
        push_postfix(&q, 1, pop_opstack(q.operators, &total_operations)->op, 0);
    }
    reverse_polish(&q);

    int result = q.final_stack->data;
    free(q.final_stack);
    return result;
}

int my_bc(char *tokens){
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    return calculate(tokens);;
}
