#pragma once

#include <iostream>
#include <string>
#include "Token.h"

class Lexer {
public:
	Lexer(std::string source);
	~Lexer() = default;

	Token getNextToken();

private:
	std::string _source;
	int _pos;
	
	Token number();
	Token string();
	Token sign();
	Token symbol();
};