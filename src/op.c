#include "../inc/my_bc.h"

int _uminus(int a, int b){
    printf("minus: a: %d, b: %d\n", a, b);
    (void)b;
    return -a;
}

int _exp(int a, int b){
    printf("exp: a: %d, b: %d\n", a, b);
    return b < 0 ? 0 : (b == 0 ? 1 : a * _exp(a, b - 1));
}

int _mul(int a, int b){
    printf("mul: a: %d, b: %d\n", a, b);
    return a * b;
}

int _div(int a, int b){
    printf("div: a: %d, b: %d\n", a, b);
    if ( ! b){
        dprintf(2, "ERROR: Division by zero\n");
        // exit(EXIT_FAILURE);
    }
    return a / b;
}

int _mod(int a, int b){
    printf("mod: a: %d, b: %d\n", a, b);
    if ( ! b) {
        dprintf(2, "ERROR: Division by zero\n");
        // exit(EXIT_FAILURE);
    }
    return a % b;
}

int _add(int a, int b){
    printf("add: a: %d, b: %d\n", a, b);
    return a + b;
}

int _sub(int a, int b){
    printf("sub: a: %d, b: %d\n", a, b);
    return a - b;
}

struct operator_type operators[]={
  {'_', 10, ASSOC_RIGHT, 1, _uminus},
  {'^', 9,  ASSOC_RIGHT, 0, _exp},
  {'*', 8,  ASSOC_LEFT,  0, _mul},
  {'/', 8,  ASSOC_LEFT,  0, _div},
  {'%', 8,  ASSOC_LEFT,  0, _mod},
  {'+', 5,  ASSOC_LEFT,  0, _add},
  {'-', 5,  ASSOC_LEFT,  0, _sub},
  {'(', 0,  ASSOC_NONE,  0, NULL},
  {')', 0,  ASSOC_NONE,  0, NULL}
};

struct operator_type *getop(char ch) {
  unsigned int i;
  for(i=0; i<sizeof operators/sizeof operators[0]; ++i) {
    if(operators[i].op==ch) return operators+i;
  }
  return NULL;
};