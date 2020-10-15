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
	auto E = (2 * x + y) ^ x; // Construct math expression (2x + y) ^ x

	printf("E = ");
	E.print();
	printf("\n");

	auto F = Sin(x) + Cos(x);
	printf("F = ");
	F.print();

	return 0;
}