#pragma once

#include <iostream>
#include <string>
#include "Semantic.h"
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"

class Interpreter {
public:
	Interpreter(std::string source);
	~Interpreter() = default;

	void interpret();

private:
	std::unique_ptr<Node> _ast;

	Semantic action(std::unique_ptr<Node> node);

	void print(Semantic sem);
	Semantic plus(Semantic left, Semantic right);
	Semantic minus(Semantic left, Semantic right);
	Semantic multiply(Semantic left, Semantic right);
	Semantic division(Semantic left, Semantic right);
};