#include <my_bc.h>

int _uminus(int a, int b){
    (void)b;
    return -a;
}

int _exp(int a, int b){
    return b < 0 ? 0 : (b == 0 ? 1 : a * _exp(a, b - 1));
}

int _mul(int a, int b){
    return a * b;
}

int _div(int a, int b){
    if ( ! b){
        dprintf(2, "ERROR: Division by zero\n");
        // exit(EXIT_FAILURE);
    }
    return a / b;
}

int _mod(int a, int b){
    if ( ! b) {
        dprintf(2, "ERROR: Division by zero\n");
        // exit(EXIT_FAILURE);
    }
    return a % b;
}

int _add(int a, int b){
    return a + b;
}

int _sub(int a, int b){
    return a - b;
}
