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

Mathematical Background
-----------------------

**Definition 1**: A *type* is a _class_ of mathematical objects such as
 - Real Numbers,
 - Complex Numbers,
 - Matrices with Real entries,
 - Sets,
 - Functions.

*Remarks*:
 1. If you are familiar with mathematical logic and set theory, Sets is a proper class in the terminology of set theory as there is no set containing of all sets. Type are not quite categories.
 2. Functions types could be further classified on the inputs such as Functions from Real Numbers to Real Numbers.
 3. For now we do not worry about *generic* types.

**Definition 2**: An *untyped language* L consists of a set of symbols.
A *typed language* L consists of a set of symbols and their corresponding types.

**Example**:
 - L = {`+`, `-`, `x`, `y`, `1`} is an untyped language consisting of 5 symbols.
 - L = {`+` : (R, R) -> R, `-`: (R, R) -> R, `x` : R, `y` : R, `1`: R} is the typed language with the same symbols in which x, y are of type Real Numbers and +, - are functions taking a pair of Real Numbers and returning a Real Number.

*Remark*:
 1. At this stage, we do not have any idea about the symbol `+` and it does not have to be "addition of real numbers". In other words, at this point, the symbols + and f are indistinguisable as long as they have the same type.
 2. Similarly, `1` does not have to be the familiar number `1`. It is indistinguisable from `x`.
 3. We could have an arity annotation in untyped language.
 4. We assume that parentheses `(` and `)` are NEVER in a language.

**Definition 3**: Given a fixed untyped language L. We can now define a concept of algebraic expressions recursively:
 - Base case: Any symbol in L is an algebraic expression.
 - Induction: If E_0, ..., E_n are algebraic expressions then E_0(E_1, E_2, ..., E_n) also is.

**Example**:
 - `+`, `x`, `y`, `+(x, y)`, `-(+(x, 1), y)`, `+(-(x))`, `+(-,x,y)`, ... are algebraic expressions for the untyped language L = {`+`, `-`, `x`, `y`, `1`} above.
 - Note that weird things like `+(-, x, y)` are not ruled out because of the lack of types. In fact, `-` itself could be a "variable" like `x`.
 
**Definition 4**: Likewise, given a typed language L, we can define an algebraic language of type T recursively:
 - Base case: A symbol of type T is an algebraic expression of type T.
 - Induction: If E_0 is an algebraic expression of function type (T1, ..., T_n) -> T and E_i is an algebraic expression of type T_i for i = 1, 2, ..., n the function application E_0(E_1, ...,E_n) is an algebraic expression of type T.

**Example**: Unlike the untyped case, we have:
 - `+` is an expression of type (R, R) -> R.
 - `x`, `y` and `+(x, y)` are expressions of type R. So is `+(+(x, y), y)`.
 - `+(x, y, +(x, y))` is a not an expression.
 - `+(-)` is not an algebraic expression. (There is no way to come up with a type).

Note that algebraic expressions depends on the language!
Different languages provides different algebraic expressions, just like adding new functions allows us to write more expressions in mathematics.
