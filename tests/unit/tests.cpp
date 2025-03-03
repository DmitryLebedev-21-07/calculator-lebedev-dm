#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

extern "C" {
    double evaluate_expression(const char **expr, int *error);
    double parse_term(const char **expr, int *error);
    double parse_factor(const char **expr, int *error);
    double parse_number(const char **expr, int *error);
    void skip_whitespace(const char **expr);
}

// Тест пропуска пробелов
TEST(CalculatorTest, SkipWhitespace) {
    const char *expr = "  42";
    skip_whitespace(&expr);
    ASSERT_EQ(*expr, '4');
}

// Тест разбора числа
TEST(CalculatorTest, ParseNumber) {
    const char *expr = "12345";
    int error = 0;
    ASSERT_EQ(parse_number(&expr, &error), 12345);
    ASSERT_EQ(error, 0);
}

// Тест разбора фактора — число
TEST(CalculatorTest, ParseFactor_Number) {
    const char *expr = "78";
    int error = 0;
    ASSERT_EQ(parse_factor(&expr, &error), 78);
    ASSERT_EQ(error, 0);
}

// Тест разбора фактора — скобки
TEST(CalculatorTest, ParseFactor_Parentheses) {
    const char *expr = "(3+2)";
    int error = 0;
    ASSERT_EQ(parse_factor(&expr, &error), 5);
    ASSERT_EQ(error, 0);
}

// Тест деления на 0
TEST(CalculatorTest, ParseTerm_DivideByZero) {
    const char *expr = "10/0";
    int error = 0;
    ASSERT_EQ(parse_term(&expr, &error), 0);
    ASSERT_NE(error, 0);
}

// Тест сложения
TEST(CalculatorTest, ParseExpression_Addition) {
    const char *expr2 = "10 - 4";
    	int error = 0;
    	ASSERT_EQ(evaluate_expression(&expr2, &error), 6);
    	ASSERT_EQ(error, 0);
}
