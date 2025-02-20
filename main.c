#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR 1024

char *expr;

int get_number(char **s) {
    int num = 0;
    while (**s && isdigit(**s)) {
        num = num * 10 + (**s - '0');
        (*s)++;
    }
    return num;
}

int eval_expr(char **s);

int eval_factor(char **s) {
    while (**s == ' ') (*s)++;
    if (**s == '(') {
        (*s)++;
        int res = eval_expr(s);
        while (**s == ' ') (*s)++;
        if (**s == ')') (*s)++;
        return res;
    }
    return get_number(s);
}

int eval_term(char **s) {
    int res = eval_factor(s);
    while (1) {
        while (**s == ' ') (*s)++;
        if (**s == '*') {
            (*s)++;
            res *= eval_factor(s);
        } else if (**s == '/') {
            (*s)++;
            res /= eval_factor(s);
        } else {
            break;
        }
    }
    return res;
}

int eval_expr(char **s) {
    int res = eval_term(s);
    while (1) {
        while (**s == ' ') (*s)++;
        if (**s == '+') {
            (*s)++;
            res += eval_term(s);
        } else if (**s == '-') {
            (*s)++;
            res -= eval_term(s);
        } else {
            break;
        }
    }
    return res;
}

int main() {
    char buffer[MAX_EXPR];
    if (!fgets(buffer, MAX_EXPR, stdin)) return 1;
    expr = buffer;
    char *ptr = expr;
    printf("%d\n", eval_expr(&ptr));
    return 0;
}