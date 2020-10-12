Symbolic Algebra Library
========================

Features and Examples
---------------------

This library allows for defining, evaluating and manipulating algebraic expressions.

Example Program:

    Variable x("x");
    Variable y("y");
    Expression E = x + y;
    E.print(); // x + y
    E.evaluate(Bind(x, 5), Bind(y, 2)); // 7
