#include "Interpreter.h"

Interpreter::Interpreter(std::string source)
	:_var(), _adress(), _varNum(0)
{
	Lexer lexer(source);
	Parser parser(lexer);
	_ast = parser.parse();

	_ast->show(0);
}

void Interpreter::interpret() {
	action(std::move(_ast));
}

bool Interpreter::isNum(Semantic sem) {
	if (sem.getType() == SemanticType::NUMBER || sem.getType() == SemanticType::VARIABLE) {
		return true;
	}
	else {
		return false;
	}
}

Semantic Interpreter::action(std::unique_ptr<Node> node) {
	if (NumberNode* num = dynamic_cast<NumberNode*>(node.get())) {
		return Semantic(num->getNumber());
	}
	else if (StringNode* str = dynamic_cast<StringNode*>(node.get())) {
		return Semantic(str->getString());
	}
	else if (VariableNode* var = dynamic_cast<VariableNode*>(node.get())) {
		return Semantic(var->getName(), getVar(var->getName()));
	}
	else if (UnaryNode* unary = dynamic_cast<UnaryNode*>(node.get())) {
		Semantic sem = action(unary->getNode());
		switch (unary->getOp()) {
			case eTokenType::PRINT: print(sem); break;
			default: std::cerr << "InterpretError : unknown unary token" << std::endl; exit(-1);
		}
	}
	else if (BinaryNode* binary = dynamic_cast<BinaryNode*>(node.get())) {
		std::unique_ptr<Node> Lnode, Rnode;
		binary->getNodes(Lnode, Rnode);
		Semantic left = action(std::move(Lnode)), right = action(std::move(Rnode));
		switch (binary->getOp()) {
			case eTokenType::PLUS: return plus(left, right);
			case eTokenType::MINUS: return minus(left, right);
			case eTokenType::MULTIPLY: return multiply(left, right);
			case eTokenType::DIVISION: return division(left, right);
			case eTokenType::VARDEF: defVar(left.getString(), right); break;
			case eTokenType::ASSIGN: assign(left.getString(), right);  break;
			case eTokenType::SEMICOLON: return Semantic();
			default: std::cerr << "InterpretError : unknwon binary token" << std::endl; exit(-1);
		}
	}
	return Semantic();
}

void Interpreter::print(Semantic sem) {
	switch (sem.getType()) {
		case SemanticType::NUMBER: 
			std::cout << sem.getNumber() << std::endl;
			break;
		case SemanticType::STRING: 
			std::cout << sem.getString() << std::endl;
			break;
		case SemanticType::VARIABLE: 
			std::cout << sem.getNumber() << std::endl;
			break;
		default:
			std::cerr << "InterpretError : print argument must be number or string" << std::endl;
			exit(-1);
			break;
	}
}

void Interpreter::assign(std::string name, Semantic val) {
	if (_adress.count(name)) {
		_var[_adress.at(name)] = val.getNumber();
	}
	else {
		std::cerr << "InterpretError : assigned not declared variable" << std::endl;
		exit(-1);
	}
}

void Interpreter::defVar(std::string name, Semantic val) {
	if (_adress.count(name)) {
		std::cerr << "InterpretError : declare declared variable" << std::endl;
		exit(-1);
	}
	else {
		_adress.emplace(name, _varNum);
		_var.push_back(val.getNumber());
		_varNum++;
	}
}

float Interpreter::getVar(std::string name) {
	if (_adress.count(name)) {
		return _var[_adress.at(name)];
	}
	else {
		//std::cerr << "InterpretError : called not declared variable" << std::endl;
		//exit(-1);
	}
}

Semantic Interpreter::plus(Semantic left, Semantic right) {
	if (isNum(left) && isNum(right) || left.getType() == right.getType()) {
		if (left.getType() == SemanticType::STRING) {
			return left.getString() + right.getString();
		}
		else {
			return left.getNumber() + right.getNumber();
		}
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::minus(Semantic left, Semantic right) {
	if (isNum(left) && isNum(right)) {
		return left.getNumber() - right.getNumber();
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::multiply(Semantic left, Semantic right) {
	if (isNum(left) && isNum(right)) {
		return left.getNumber() * right.getNumber();
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::division(Semantic left, Semantic right) {
	if (isNum(left) && isNum(right)) {
		return left.getNumber() / right.getNumber();
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}