#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Expression.h"

int main(int argc, const char **argv)
{
	Variable x("x");
	Variable y("y");
	Expression E = x + y;
	E.print();

	return 0;
}