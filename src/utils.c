#include "../inc/my_bc.h"

int is_digit(char c){
    return c >= '0' && c <= '9';
}

int is_operator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '_';
}

int is_alpha(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}