#include <my_bc.h>

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int parse(const char *tokens){
    struct queue q = {
        .stack1 = NULL,
        .stack2 = NULL
    };
    // struct stack operators = Stack.new();
    if (tokens == NULL){
        dprintf(2, "parse error\n");
        return EXIT_FAILURE;
    }
    while (*tokens){
        switch (*tokens){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            dprintf(1, "number: %c\n", *tokens);
            enqueue(&q, *tokens - 48);
            break;
        case '_':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            dprintf(1, "operator: %c\n", *tokens);
            // 5.While there'tokens an operator on the top of the stack with greater precedence:
            // 6.Pop operators from the stack onto the output queue
            // 7.Push the current operator onto the stack
            break;
        case '(':
            dprintf(1, "left bracket: %c\n", *tokens);
            // push it onto the stack
            break;
        case ')':
            dprintf(1, "right bracket: %c\n", *tokens);
            // 10. While there'tokens not a left bracket at the top of the stack:
            // 11.      Pop operators from the stack onto the output queue.
            // 12. Pop the left bracket from the stack and discard it
            break;
        }
        tokens += 1;
    }
    // 13. While there are operators on the stack, pop them to the queue
    display(q.stack1, q.stack2);
    return EXIT_SUCCESS;
}

int my_bc(const char *tokens){
    return parse(tokens);;
}
