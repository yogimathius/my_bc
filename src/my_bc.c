#include <my_bc.h>

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

/**
 * Shunting Yard Algorithm Pseudocode
 * from https://brilliant.org/wiki/shunting-yard-algorithm/
    1.  While there are tokens to be read:
    2.        Read a token
    3.        If it's a number add it to queue
    4.        If it's an operator
    5.               While there's an operator on the top of the stack with greater precedence:
    6.                       Pop operators from the stack onto the output queue
    7.               Push the current operator onto the stack
    8.        If it's a left bracket push it onto the stack
    9.        If it's a right bracket 
    10.            While there's not a left bracket at the top of the stack:
    11.                     Pop operators from the stack onto the output queue.
    12.             Pop the left bracket from the stack and discard it
    13. While there are operators on the stack, pop them to the queue
*/
void parse(const char *s){
    while (*s != '\0'){
        if (*s == '('){
            dprintf(1, "left bracket: %s\n", s);
        }
        else if (*s == ')'){
            dprintf(1, "right bracket: %s\n", s);
        }
        else if (*s == '+' || *s == '-' || *s == '*' || *s == '/'){
            dprintf(1, "operator: %c\n", *s);
        }
        else if (*s >= '0' && *s <= '9'){
            dprintf(1, "number: %c\n", *s);
        }
        s++;
    }
}

int my_bc(const char *s){
    int num = 0;
    if (s == NULL){
        dprintf(2, "parse error\n");
        return 1;
    }
    parse(s);
    return num;
}
