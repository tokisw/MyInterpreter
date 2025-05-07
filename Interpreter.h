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
	std::shared_ptr<Node> _ast;

	int _varNum;
	std::map<std::string, int> _varAddress;
	std::vector<float> _var;

	int _funcNum;
	std::map<std::string, int> _funcAddress;
	std::vector<std::shared_ptr<Node>> _funcProgram;
	std::vector<std::vector<std::string>> _funcArguments;

	bool isNum(Semantic sem);

	Semantic action(std::shared_ptr<Node> node);

	void defFunc(std::string name, std::shared_ptr<Node> arguments, std::shared_ptr<Node> program);
	Semantic callFunc(std::string name, std::vector<Semantic> arguments);
	std::vector<std::string> openArgumentsSY(std::shared_ptr<Node> arguments);
	std::vector<Semantic> openArgumentsSE(std::shared_ptr<Node> arguments);

	void print(Semantic sem);

	void assign(std::string name, Semantic val);
	void defVar(std::string name, Semantic val);
	void delVar(std::string name);
	float getVar(std::string name);

	Semantic plus(Semantic left, Semantic right);
	Semantic minus(Semantic left, Semantic right);
	Semantic multiply(Semantic left, Semantic right);
	Semantic division(Semantic left, Semantic right);
};