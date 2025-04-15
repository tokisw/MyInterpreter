#pragma once

#include <iostream>
#include <memory>$
#include "Lexer.h"
#include "Node.h"

class Parser {
public:
	Parser(Lexer lexer);
	~Parser() = default;

	std::unique_ptr<Node> parse();

private:
	Lexer _lexer;
	Token _currentToken;

	void shift(eTokenType type);

	std::unique_ptr<Node> program();
	std::unique_ptr<Node> statement();
	std::unique_ptr<Node> compound();
	std::unique_ptr<Node> declaration();
	std::unique_ptr<Node> call_func();
	std::unique_ptr<Node> expression();
	std::unique_ptr<Node> term();
	std::unique_ptr<Node> factor();
};

/*
　プログラム
program ::= ( statement )*

　文
statement ::= PRINT "(" expression ")" ";"
              | define_var ";"
			  | SYMBOL  "=" expression ";"
			  | compound
			  @ call_func ";"

compound ::= "{" statement* "}"

　宣言
declaration ::= VAR SYMBOL ( "=" expression )
			    | FUNC SYMBOL "(" ( arg_name ( "," arg_name )* ) ")" compound

　関数呼び出し
@ call_func ::= SYMBOL "(" ( value ( "," value )* ")"

　式
expression ::= term ( ( "+" | "-" ) temr )*
　
　項
term ::= factor ( ( "*" | "/" )  factor )*
　
　因子
factor ::= NUMBER
		   | STRING
		   | "(" expression ")"
		   | SYMBOL
		   @ call_func
*/