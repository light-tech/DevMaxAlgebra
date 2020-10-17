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

// Template method to perform action on each element of a list
// The action should take an TElement and a bool indicating whether
// that was the last element of the list
template<typename TElement, typename TAction>
void ForEach(TAction action, LTList<TElement> *list) {
	if(list != nullptr) {
		action(list->data, list->next == nullptr);
		ForEach(action, list->next);
	}
}

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
	/*class Type {
		int classification; // Number, Set, Function, ...
		int arity;          // Tuples
	};*/

	// Kind of the expression corresponding to the base case and recursion
	enum Kind {
		Symbol,         // A symbol in the language
		FunctionApply,  // A function application
		Tuple,          // A tuple
	};

	Kind kind;                           // kind of the expression
	//Type *type;                          // type of the expression, currently unused
	const char *name;                    // name of the symbol, if kind is Symbol
	LTList<Expression> *subexpressions;  // subexpressions for Function and Tuple kind

	// Default constructor so that we can use LTList<Expression>
	Expression() : kind(Kind::Symbol), name("?unknown?") {
	}

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
	Expression evaluate() {
		return nullptr;
	}

	// Pre-defined symbols in the language for common math operators and functions
	//      +, -, x, /, exp, sin, cos, ...
	// These objects are given standard bindings upon evaluation.
	static Expression OpAdd;
	static Expression OpSubtract;
	static Expression OpMultiply;
	static Expression OpDivide;
	static Expression OpExponentiation;
	static Expression FuncSqrt;
	static Expression FuncSin;
	static Expression FuncCos;
	static Expression FuncTan;
	static Expression FuncExp;
	static Expression FuncLn;

	// Static helper method to make Tuple expression
	template<typename T, typename ...Ts>
	static Expression makeTuple(T first, Ts ...rest) {
		Expression result(Kind::Tuple);
		result.subexpressions = new LTList<Expression>(first, rest...);

		return result;
	}

	// Static helper method to make Function application expressions
	static Expression makeFunctionApplication(Expression const& func, Expression const& args) {
		Expression result(Kind::FunctionApply);
		result.subexpressions = new LTList<Expression>(func, args);

		return result;
	}
};

// Declaration of our predefined constants for overloadable basic arithmetic operators
Expression Expression::OpAdd("+");
Expression Expression::OpSubtract("-");
Expression Expression::OpMultiply("*"); // Must not use 'x' for this could cause confusion with variable x
Expression Expression::OpDivide("/");
Expression Expression::OpExponentiation("^");
Expression Expression::FuncSqrt("sqrt");
Expression Expression::FuncSin("sin");
Expression Expression::FuncCos("cos");
Expression Expression::FuncTan("tan");
Expression Expression::FuncExp("exp");
Expression Expression::FuncLn("ln");

// To allow for writing 'x + y' in C++ where 'x', 'y' are Expression, we define
// the global operators in the following signature:
//      Expression operator+(Expression const&, Expression const&);
// We make a macro to do this for many operators at once.

#define _IMPLEMENT_EXPRESSION_OPERATOR(Op, OpExpr) Expression operator Op (Expression const& first, Expression const& second) {\
	auto args = Expression::makeTuple(first, second);\
	auto result = Expression::makeFunctionApplication(OpExpr, args);\
	return result;\
}

_IMPLEMENT_EXPRESSION_OPERATOR(+, Expression::OpAdd)
_IMPLEMENT_EXPRESSION_OPERATOR(-, Expression::OpSubtract)
_IMPLEMENT_EXPRESSION_OPERATOR(*, Expression::OpMultiply)
_IMPLEMENT_EXPRESSION_OPERATOR(/, Expression::OpDivide)
_IMPLEMENT_EXPRESSION_OPERATOR(^, Expression::OpExponentiation)

// For math functions like sin, cos, ...; we make subclasses from Expressions.
// This way, we could write
//        Expression E = Sin(x);
// in the program. The implementation looks pretty much the same so we make
// a macro to do so for many functions.
#define _DECLARE_STANDARD_FUNCTION_APPLICATION(FunctionName) class FunctionName : public Expression {\
public:\
	FunctionName(Expression const& arg) : Expression(Kind::FunctionApply) {\
		this->subexpressions = new LTList<Expression>(Func ## FunctionName, arg);\
	}\
};

_DECLARE_STANDARD_FUNCTION_APPLICATION(Sqrt)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Sin)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Cos)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Tan)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Exp)
_DECLARE_STANDARD_FUNCTION_APPLICATION(Ln)

// Print expression to standard output
static void print(Expression const& expr) {
	switch (expr.kind) {
	case Expression::Kind::Symbol:
		printf("%s", expr.name);
		break;

	case Expression::Kind::FunctionApply:
		ForEach([](Expression const& e, bool is_last) {
			print(e);
			if (!is_last) printf(" ");
		}, expr.subexpressions);
		break;

	case Expression::Kind::Tuple:
		printf("(");
		ForEach([](Expression const& e, bool is_last) {
			print(e);
			if (!is_last) printf(", ");
		}, expr.subexpressions);
		printf(")");
		break;
	}
}

#endif