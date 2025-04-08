#pragma once

#include <iostream>
#include <memory>
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
	std::unique_ptr<Node> expression();
	std::unique_ptr<Node> term();
	std::unique_ptr<Node> factor();
};

/*

program ::= ( statement )*

statement ::= PRINT "(" expression ")" ";"

definition :: VAR STRING ( "=" expression )

expression ::= term ( ( "+" | "-" ) temr )*

term ::= factor ( ( "*" | "/" )  factor )*

factor ::= NUMBER
		   | STRING
		   | "(" expression ")"
*/