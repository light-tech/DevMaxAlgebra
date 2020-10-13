#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Expression.h"

int main(int argc, const char **argv)
{
	Symbol x("x");
	Symbol y("y");
	Expression* E = x + y;

	if (E != nullptr)
		E->print();

	return 0;
}