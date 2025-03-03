#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_NUMBER 2000000000 // 2 * 10^9

// Function prototypes
double evaluate_expression(const char** expr, int* error);
double parse_term(const char** expr, int* error);
double parse_factor(const char** expr, int* error);
double parse_number(const char** expr, int* error);
void skip_whitespace(const char** expr);

#ifndef UNIT_TEST
int main(int argc, char* argv[])
{
    char input[MAX_INPUT_SIZE];
    int float_mode = 0;

    // Check for --float flag
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--float") == 0) {
            float_mode = 1;
        }
    }

    // Read input from user
    if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
        return 1;
    }

    // Remove newline character if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Validate allowed charset
    for (size_t i = 0; i < len; i++) {
        if (!strchr("0123456789()+-*/. ", input[i])) {
            return 1;
        }
    }

    int error = 0;
    const char* expr = input; // Создаем указатель на строку
    double result = evaluate_expression(&expr, &error); // Передаем адрес указателя

    // Проверка на превышение максимального числа
    if (result > MAX_NUMBER) {
        return 1;
    }

    if (error) {
        return 1;
    }

    // Print result in correct format
    if (float_mode) {
        printf("%.6f\n", result);
    } else {
        printf("%d\n", (int)result);
    }

    return 0;
}
#endif

// Function to evaluate an arithmetic expression
double evaluate_expression(const char** expr, int* error)
{
    skip_whitespace(expr);
    double result = parse_term(expr, error);
    while (**expr) {
        skip_whitespace(expr);
        if (**expr == '+' || **expr == '-') {
            char op = **expr;
            (*expr)++;
            skip_whitespace(expr);
            double next_value = parse_term(expr, error);
            if (op == '+')
                result += next_value;
            else
                result -= next_value;
        } else {
            break;
        }
    }
    return result;
}

// Parse terms (handles multiplication and division)
double parse_term(const char** expr, int* error)
{
    skip_whitespace(expr);
    double value = parse_factor(expr, error);
    while (**expr == '*' || **expr == '/') {
        skip_whitespace(expr);
        char op = **expr;
        (*expr)++;
        skip_whitespace(expr);
        double next_value = parse_factor(expr, error);
        if (op == '/' && next_value == 0) {
            *error = 1;
            return 0;
        }
        if (op == '*')
            value *= next_value;
        else
            value /= next_value;
    }
    return value;
}

// Parse factors (handles parentheses and numbers)
double parse_factor(const char** expr, int* error)
{
    skip_whitespace(expr);
    if (**expr == '(') {
        (*expr)++;
        double value = evaluate_expression(expr, error);
        skip_whitespace(expr);
        if (**expr == ')') {
            (*expr)++;
        } else {
            *error = 1;
            return 0;
        }
        return value;
    }
    return parse_number(expr, error);
}

// Parse numbers (handles numeric values)
double parse_number(const char** expr, int* error)
{
    skip_whitespace(expr);
    if (!isdigit(**expr) && **expr != '.') {
        *error = 1;
        return 0;
    }
    char* end;
    double value = strtod(*expr, &end);
    if (*expr == end) {
        *error = 1;
        return 0;
    }
    *expr = end;
    return value;
}

// Skip whitespace
void skip_whitespace(const char** expr)
{
    while (**expr && isspace(**expr))
        (*expr)++;
}
