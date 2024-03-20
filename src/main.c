#include <stdio.h>
#include "../inc/my_bc.h"

int main(const int ac, const char **av){
    if (ac == 2){
        int result = my_bc(av[1]);
        printf("%d\n", result);
        return result;
    }
    help();
    return EXIT_SUCCESS;
}