#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

class Expression;
#include "Expression.h"

// Data for generating random expressions
class Configuration {
public:
	Expression *symbols;
	int num_symbols;

	Expression *functions;
	int *functions_arity;
	int num_functions;
};

Expression generateRandomExpression(int level, Configuration const& config) {
	if (level == 0)
		return rand() % 20; // return a random integer constant expression

	// Randomly decide if we should make a function f(), a symbol or constant
	// We give higher probability to function and symbols!
	int target = rand() % 10; // 0 .. 9
	if (target <= 5) { // 0 .. 5
		auto f = rand() % config.num_functions;
		int k = config.functions_arity[f];
		auto func = config.functions[f];
		if (k == 1) {
			auto arg = generateRandomExpression(level - 1, config);
			return Expression::makeFunctionApplication(func, arg);
		} else {
			// For now k should be 2 here
			// We might want to think about higher arity later
			auto arg1 = generateRandomExpression(level - 1, config);
			auto arg2 = generateRandomExpression(level - 1, config);
			auto args = Expression::makeTuple(arg1, arg2);
			return Expression::makeFunctionApplication(func, args);
		}
	} else if (target <= 7) { // 6 .. 7
		auto s = rand() % config.num_symbols;
		return config.symbols[s];
	} else { // 8 .. 9
		return rand() % 20;
	}
}

void TestBasicSyntax() {
	Expression x("x");        // Make variable named x
	Expression y("y");        // Make variable named y

	auto E = (2 * x + y) / x; // Construct a simple math expression
	printf("E = ");
	printLaTeX(E);
	printf("\n");

	// Note that C++ operator ^ has lower precedence than + so we must put
	// parentheses around x^2 otherwise it would be interpreted as x^(2 + 1).
	auto F = (3 * Sin(x) - Cos(x)) * Tan((x^2) + 1);
	printf("F = ");
	printLaTeX(F);
}

void TestExpressionGeneration() {
	Configuration config;
	config.symbols = new Expression[10];
	config.functions = new Expression[10];
	config.functions_arity = new int[10];

	Expression x("x");
	config.symbols[0] = x;
	config.num_symbols = 1;

	config.functions[0] = Expression::FuncSqrt;
	config.functions[1] = Expression::OpAdd;
	config.functions[2] = Expression::OpSubtract;
	config.functions[3] = Expression::OpMultiply;
	config.functions[4] = Expression::OpDivide;
	config.num_functions = 5;

	config.functions_arity[0] = 1;
	for(int i = 1; i < 5; i++)
		config.functions_arity[i] = 2;

	for(int i = 0; i < 500; i++) {
		auto expr = generateRandomExpression(5, config);
		printf("$$");
		printLaTeX(expr);
		printf("$$\n");
	}
}

int main(int argc, const char **argv)
{
	srand(time(NULL));
	TestExpressionGeneration();

	return 0;
}