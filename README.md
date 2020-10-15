Symbolic Algebra Library
========================

Features and Examples
---------------------

This library allows for defining, evaluating and manipulating algebraic expressions.
The mathematical basis can be found in [MathBasis.tex](MathBasis.tex).

Example Program:

```C++
    Expression x("x");
    Expression y("y");
    auto E = (x + y) ^ x;

    printf("E = ");
    E.print();

    auto F = Sin(x) + Cos(x);
    printf("F = ");
	F.print();

    E.evaluate(Bind(x, 5), Bind(y, 2)); // 7
```
