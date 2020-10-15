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
		int arity;          // Tuples
	};

	// Kind of the expression corresponding to the base case and recursion
	enum Kind {
		Symbol,    // A symbol in the language
		Function,  // A function application
		Tuple      // A tuple
	};

	// Constant are pre-defined symbols such as
	//      [Numbers]      1, 1/2, \pi
	//      [Operator]     +, -, x, /, exp, sin, cos, ...
	// and are given standard bindings upon evaluation.
	// Non-constant symbols are variables like x, y, F.
	static Expression Add;
	static Expression Subtract;
	static Expression Multiply;
	static Expression Divide;
	static Expression Exponentiation;
	static Expression FuncSin;
	static Expression FuncCos;
	static Expression FuncTan;
	static Expression FuncExp;
	static Expression FuncLn;

	Kind kind;                           // kind of the expression
	Type *type;                          // type of the expression, currently unused
	const char *name;                    // name of the symbol, if kind is Symbol
	LTList<Expression*> *subexpressions; // subexpressions for Function and Tuple kind

	// Construct an uninitialized expression of given kind
	Expression(Kind kind) {
		this->kind = kind;
		subexpressions = nullptr;
	}

	// Construct a new Symbol in the language with specified name
	Expression(const char *name) : kind(Kind::Symbol) {
		this->name = name;
	}

	// Construct constant expression for an integer
	Expression(int n) : kind(Kind::Symbol) {
		char buf[20];
		_itoa(n, buf, 10);
		this->name = _strdup(buf);
	}

	template<typename ...Ts>
	Expression* evaluate() {
		return nullptr;
	}

	// Print this expression to standard output
	void print() {
		switch (kind) {
		case Kind::Symbol:
			printf("%s", name);
			break;

		case Kind::Function:
			printExpressionList("   ", subexpressions);
			break;

		case Kind::Tuple:
			printf("(");
			printExpressionList(" , ", subexpressions);
			printf(")");
			break;
		}
	}

	Expression operator+(Expression const& another);
	Expression operator-(Expression const& another);
	Expression operator*(Expression const& another);
	Expression operator/(Expression const& another);
	Expression operator^(Expression const& another);

	// Static helper method to make Tuple expression
	template<typename T, typename ...Ts>
	static Expression* makeTuple(T first, Ts ...rest) {
		auto result = new Expression(Expression::Kind::Tuple);
		result->subexpressions = new LTList<Expression*>(first, rest...);

		return result;
	}

	// Static helper method to make Function application expressions
	static Expression makeFunction(Expression *func, Expression *args) {
		Expression result(Expression::Kind::Function);
		result.subexpressions = new LTList<Expression*>(func, args);

		return result;
	}

private:
	// Helper method to print out a list of expressions, separated by given string
	static void printExpressionList(const char* separator, LTList<Expression*> *expressions) {
		if (expressions != nullptr) {
			expressions->data->print();
			if (expressions->next != nullptr) {
				printf("%s", separator);
				printExpressionList(separator, expressions->next);
			}
		}
	}
};

// Declaration of our predefined constants for overloadable basic arithmetic operators
Expression Expression::Add("+");
Expression Expression::Subtract("-");
Expression Expression::Multiply("*"); // Must not use 'x' for this could cause confusion with variable x
Expression Expression::Divide("/");
Expression Expression::Exponentiation("^");
Expression Expression::FuncSin("sin");
Expression Expression::FuncCos("cos");
Expression Expression::FuncTan("tan");
Expression Expression::FuncExp("exp");
Expression Expression::FuncLn("ln");

#define _IMPLEMENT_OPERATOR(Op, OpExpr) Expression Expression::operator Op (Expression const& another) {\
	auto args = makeTuple(this, const_cast<Expression*>(&another));\
	auto result = makeFunction(&OpExpr, args);\
	return result;\
}\
Expression operator Op (Expression const& first, Expression const& second) {\
	auto args = Expression::makeTuple(const_cast<Expression*>(&first), const_cast<Expression*>(&second));\
	auto result = Expression::makeFunction(&OpExpr, args);\
	return result;\
}

_IMPLEMENT_OPERATOR(+, Expression::Add)
_IMPLEMENT_OPERATOR(-, Expression::Subtract)
_IMPLEMENT_OPERATOR(*, Expression::Multiply)
_IMPLEMENT_OPERATOR(/, Expression::Divide)
_IMPLEMENT_OPERATOR(^, Expression::Exponentiation)

// For math functions like sin, cos, ...; we subclasses from Expressions.
// This way, we could write
//        auto E = Sin(x);
// in the program. The implementation looks pretty much the same so we make
// a macro to do so for many functions.
#define _DECLARE_STANDARD_FUNCTION_APPLICATION(FunctionName) class FunctionName : public Expression {\
public:\
	FunctionName(Expression &arg) : Expression(Kind::Function) {\
		this->subexpressions = new LTList<Expression*>(&Func ## FunctionName, &arg);\
	}\
};

_DECLARE_STANDARD_FUNCTION_APPLICATION(Sin)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Cos)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Tan)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Exp)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Ln)

#endif