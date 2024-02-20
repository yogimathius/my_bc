#include <my_bc.h>

void help(){
    dprintf(1, "%s: basic calculator\n", PROG_NAME);
}

int my_bc(const char *s){
    int num = 0;
    if (s == NULL){
        dprintf(2, "parse error\n");
    }
    dprintf(1, "received: '%s'\n", s);
    return num;
}
