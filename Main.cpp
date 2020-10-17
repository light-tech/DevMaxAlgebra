#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "Expression.h"

int main(int argc, const char **argv)
{
	Expression x("x");        // Make variable named x
	Expression y("y");        // Make variable named y

	auto E = (2 * x + y)^x; // Construct math expression (2x + y) ^ x + 1
	printf("E = ");
	print(E);
	printf("\n");

	// Note that C++ operator ^ has lower precedence than + so we must put
	// parentheses around x^2 otherwise it would be interpreted as x^(2 + 1).
	auto F = (3 * Sin(x) - Cos(x)) * Tan((x^2) + 1);
	printf("F = ");
	print(F);

	return 0;
}