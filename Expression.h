/*
 * Header to define data structure for an algebraic expression
 */

#ifndef __EXPRESSION_H_
#define __EXPRESSION_H_

// Linked list template
template <typename TElement>
class LTList
{
public:
	LTList(TElement d) {
		data = d;
		next = nullptr;
	}

	LTList(TElement d, LTList<TElement> *n) {
		data = d;
		next = n;
	}

	TElement data;
	LTList<TElement> *next;
};

// Mathematically, expressions are defined recursively:
//  - Base case: constants and variables are expressions
//  - Induction: if E is a k-ary function expression then
//          E ( E_1, E_2, E_3, ..., E_k )
//    is also an expression.
//
// For example, +(1, x) is an expression since + and 1 are
// constants and x is a variable of number type.
// Likewise, f(x, y) is an expression if x, y are variables
// for numbers and f is a function with 2 numbers as input.
//
// Note: It is more natural to use this prefix notation than
// the familiar 1 + x.
class Expression {
public:
	class Type {
		int classification; // Number, Set, Function, ...
	};

	LTList<Expression*> *application;
	Type *type;

	Expression() {
		application = nullptr;
		type = nullptr;
	}

	void print();
};

// Constant are pre-defined standard mathematical objects such as
//      [Numbers]      1, 1/2, \pi
//      [Operator]     +, -, x, /, exp, sin, cos, ...
class Constant : public Expression {
public:
};

// Variable are user-defined symbols such as x, y, z, f, g, h, A, B, ...
// Each variable should
class Variable : public Expression {
public:
	const char *name;

	Variable(const char *name) {
		this->name = name;
	}
};

#endif