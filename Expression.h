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

	template<typename T, typename ...Ts>
	LTList(T d, Ts ...rest) {
		data = d;
		next = new LTList(rest...);
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
		int arity; // for tuples
	};

	LTList<Expression*> *subexpressions;
	Type *type;

	Expression() {
		subexpressions = nullptr;
		type = nullptr;
	}

	template<typename ...Ts>
	Expression* evaluate() {
		return nullptr;
	}

	virtual void print() {
		printExpressionList(subexpressions);
	}

	Expression* operator+(Expression const& another);

private:
	void printExpressionList(LTList<Expression*> *expressions) {
		if (expressions != nullptr) {
			expressions->data->print();
			printf(" ");
			printExpressionList(expressions->next);
		}
	}
};

// A symbol in our language.
class Symbol : public Expression {
public:
	const char *name;

	Symbol(const char *name) {
		this->name = name;
	}

	virtual void print() { printf("%s", name); }
};

// Constant are pre-defined symbols such as
//      [Numbers]      1, 1/2, \pi
//      [Operator]     +, -, x, /, exp, sin, cos, ...
// and are given standard bindings upon evaluation.
// Non-constant symbols are variables like x, y, F.
class Constant : public Symbol {
public:
	static Constant Add;
	static Constant Subtract;
	static Constant Multiply;
	static Constant Divide;

	Constant(const char *name) : Symbol(name) {
		this->name = name;
	}
};

Constant Constant::Add("+");
Constant Constant::Subtract("-");
Constant Constant::Multiply("x");
Constant Constant::Divide("/");

Expression* Expression::operator+(Expression const& another) {
	auto result = new Expression();
	result->subexpressions = new LTList<Expression*>(&Constant::Add, this, const_cast<Expression*>(&another));
	return result;
}

#endif