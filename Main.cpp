#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Expression.h"

int main(int argc, const char **argv)
{
	Expression x("x");
	Expression y("y");
	auto E = (x + y) ^ x;

	printf("E = ");
	E.print();
	printf("\n");

	auto F = Sin(x) + Cos(x);
	printf("F = ");
	F.print();

	return 0;
}