#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
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

	int _varNum;
	std::map<std::string, int> _adress;
	std::vector<float> _var;

	bool isNum(Semantic sem);

	Semantic action(std::unique_ptr<Node> node);

	void print(Semantic sem);
	void assign(std::string name, Semantic val);
	void defVar(std::string name, Semantic val);
	float getVar(std::string name);
	Semantic plus(Semantic left, Semantic right);
	Semantic minus(Semantic left, Semantic right);
	Semantic multiply(Semantic left, Semantic right);
	Semantic division(Semantic left, Semantic right);
};