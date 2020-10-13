#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Expression.h"

int main(int argc, const char **argv)
{
	Expression x("x");
	Expression y("y");
	auto E = x + y;

	if (E != nullptr) {
		printf("E = ");
		E->print();
	}

	printf("\n");
	auto F = Sin(x);
	printf("F = ");
	F.print();

	return 0;
}