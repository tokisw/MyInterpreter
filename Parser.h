#pragma once

#include <iostream>
#include <memory>
#include "Lexer.h"
#include "Node.h"

class Parser {
public:
	Parser(Lexer lexer);
	~Parser() = default;

	std::shared_ptr<Node> parse();

private:
	Lexer _lexer;
	Token _currentToken;

	void shift(eTokenType type);

	std::shared_ptr<Node> program();
	std::shared_ptr<Node> statement();
	std::shared_ptr<Node> compound();
	std::shared_ptr<Node> declaration();
	std::shared_ptr<Node> call_func(std::shared_ptr<Node> symbol_name);
	std::shared_ptr<Node> expression();
	std::shared_ptr<Node> term();
	std::shared_ptr<Node> factor();
};

/*
　プログラム
program ::= ( statement )*

　文
statement ::= PRINT "(" expression ")" ";"
              | define_var ";"
			  | SYMBOL  "=" expression ";"
			  | compound
			  | call_func ";"

compound ::= "{" statement* "}"

　宣言
declaration ::= VAR SYMBOL ( "=" expression )
			    | FUNC SYMBOL "(" ( arg_name ( "," arg_name )* ) ")" compound

　関数呼び出し
@ call_func ::= SYMBOL "(" ( expression ( "," expression )* ")"

　式
expression ::= term ( ( "+" | "-" ) temr )*
　
　項
term ::= factor ( ( "*" | "/" )  factor )*
　
　因子
factor ::= NUMBER
		   | STRING
		   | "(" expression ")"
		   | SYMBOL
		   | call_func
*/