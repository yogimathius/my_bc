#include <my_bc.h>

int main(const int ac, const char **av){
    if (ac == 2){
        return my_bc(av[1]);
    }
    help();
    return EXIT_SUCCESS;
}