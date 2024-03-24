#include "../inc/my_bc.h"

bool is_operand(char c){
    return c >= '0' && c <= '9';
}

bool is_operator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '_';
}

bool is_alpha(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool has_higher_precedence(struct operator_type *op1, struct operator_type *op2){
    return op1->prec > op2->prec || (op1->prec == op2->prec && op1->assoc == ASSOC_RIGHT);
}

bool should_push_operator(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK], int total_operations){
    return opstack[0] == NULL || opstack[total_operations - 1]->op == '(' || has_higher_precedence(op, opstack[total_operations - 1]);
}

bool should_shunt(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK], int total_operations){
    return !should_push_operator(op, opstack, total_operations);
}