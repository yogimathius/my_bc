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