#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <my_bc.h>

void push_opstack(struct operator_type *op, struct operator_type *opstack[MAX_OP_STACK], int *total_operations)
{
  if((*total_operations)>MAX_OP_STACK-1) {
    fprintf(stderr, "ERROR: Operator stack overflow\n");
    exit(EXIT_FAILURE);
  }
  opstack[*total_operations]=op;
  (*total_operations)++;
}

struct operator_type *pop_opstack(struct operator_type *opstack[MAX_OP_STACK], int *total_operations) {
    if(opstack[(*total_operations - 1)] == NULL) {
        printf("stack empty\n");
        return NULL;
    }
    struct operator_type *op = opstack[*total_operations-1];
    opstack[*total_operations-1] = NULL;
    (*total_operations) -= 1;
    return op;
}