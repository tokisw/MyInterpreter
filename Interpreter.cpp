#include "Interpreter.h"

Interpreter::Interpreter(std::string source)
	:_var(), _varAddress(), _varNum(0), _funcProgram(), _funcArguments(), _funcAddress(), _funcNum(0)
{
	Lexer lexer(source);
	Parser parser(lexer);
	_ast = parser.parse();

	if (_ast != nullptr) {
		_ast->show(0);
	}
}

void Interpreter::interpret() {
	action(_ast);
}

bool Interpreter::isNum(Semantic sem) {
	if (sem.getType() == SemanticType::NUMBER || sem.getType() == SemanticType::VARIABLE) {
		return true;
	}
	else {
		return false;
	}
}

Semantic Interpreter::action(std::shared_ptr<Node> node) {
	if (NumberNode* num = dynamic_cast<NumberNode*>(node.get())) {
		return Semantic(num->getNumber());
	}
	else if (StringNode* str = dynamic_cast<StringNode*>(node.get())) {
		return Semantic(str->getString());
	}
	else if (SymbolNode* sym = dynamic_cast<SymbolNode*>(node.get())) {
		return Semantic(sym->getName(), getVar(sym->getName()));
	}
	else if (UnaryNode* unary = dynamic_cast<UnaryNode*>(node.get())) {
		Semantic sem = action(unary->getNode());
		switch (unary->getOp()) {
			case eTokenType::PRINT: print(sem); break;
			default: std::cerr << "InterpretError : unknown unary token" << std::endl; exit(-1);
		}
	}
	else if (BinaryNode* binary = dynamic_cast<BinaryNode*>(node.get())) {
		std::shared_ptr<Node> Lnode, Rnode;
		binary->getNodes(Lnode, Rnode);

		if (binary->getOp() == eTokenType::VARDEF) {
			Semantic right = action(Rnode);
			if (SymbolNode* sym = dynamic_cast<SymbolNode*>(Lnode.get())) {
				defVar(sym->getName(), right);
			}
			else {
				std::cerr << "InterpretError : variable name must be symbol" << std::endl;
				exit(-1);
			}
			return Semantic();
		}
		else if (binary->getOp() == eTokenType::FUNC) {
			if (SymbolNode* name = dynamic_cast<SymbolNode*>(Lnode.get())) {
				return callFunc(name->getName(), openArgumentsSE(Rnode));
			}
			else {
				std::cerr << "InterpretError : called undefined function" << std::endl;
				exit(-1);
			}
		}
		Semantic left = action(Lnode), right = action(Rnode);
		switch (binary->getOp()) {
			case eTokenType::PLUS: return plus(left, right);
			case eTokenType::MINUS: return minus(left, right);
			case eTokenType::MULTIPLY: return multiply(left, right);
			case eTokenType::DIVISION: return division(left, right);
			case eTokenType::ASSIGN: assign(left.getString(), right);  break;
			case eTokenType::SEMICOLON: return Semantic();
			default: std::cerr << "InterpretError : unknwon binary token" << std::endl; exit(-1);
		}
	}
	else if (TernaryNode* ternary = dynamic_cast<TernaryNode*>(node.get())) {
		std::shared_ptr<Node> Lnode, Cnode, Rnode;
		ternary->getNodes(Lnode, Cnode, Rnode);
		switch (ternary->getOp()) {
			case eTokenType::FUNCDEF: {
				if (SymbolNode* name = dynamic_cast<SymbolNode*>(Lnode.get())) {
					defFunc(name->getName(), Cnode, Rnode);
				}
				else {
					std::cerr << "InterpretError : function name must be symbol" << std::endl;
					exit(-1);
				}
				break;
			}
			default: std::cerr << "InterpreterError: unknown ternary token" << std::endl; exit(-1);
		}
	}
	return Semantic();
}

void Interpreter::defFunc(std::string name, std::shared_ptr<Node> arguments, std::shared_ptr<Node> program) {
	if (_funcAddress.count(name)) {
		std::cerr << "InterpreterError : define defined function" << std::endl;
		exit(-1);
	}
	else {
		_funcAddress.emplace(name, _funcNum);
		_funcProgram.push_back(program);
		_funcArguments.push_back(openArgumentsSY(arguments));
		_funcNum++;
	}
}

Semantic Interpreter::callFunc(std::string name, std::vector<Semantic> arguments) {
	if (!_funcAddress.count(name)) {
		std::cerr << "InterpretError : call not defined function" << std::endl;
		exit(-1);
	}
	int address = _funcAddress[name];
	if (arguments.size() != _funcArguments[address].size()) {
		std::cerr << "InterpretError : not matched arguments" << std::endl;
		std::cerr << "defined_size:" << _funcArguments[address].size() << " given_size:" << arguments.size() << std::endl;
		exit(-1);
	}
	int temp_var_num = _varNum;
	std::map<std::string, int> temp_address = _varAddress;
	//Å™í¥èdÇ¢â¬î\ê´ëÂ
	for (int i = 0; i < arguments.size(); i++) {
		defVar(_funcArguments[address][i], arguments[i]);
	}
	Semantic res = action(_funcProgram[address]);
	_varAddress = temp_address;
	_varNum = temp_var_num;
	return res;
}

std::vector<std::string> Interpreter::openArgumentsSY(std::shared_ptr<Node> arguments) {
	std::vector<std::string> res;
	if (arguments == nullptr) {
		return res;
	}
	std::shared_ptr<Node> node = arguments;
	while (BinaryNode* binary = dynamic_cast<BinaryNode*>(node.get())) {
		std::shared_ptr<Node> left, right;
		binary->getNodes(left, right);
		if (SymbolNode* sym = dynamic_cast<SymbolNode*>(right.get())) {
			res.push_back(sym->getName());
		}
		else {
			std::cerr << "InterpretError : function arguments name must be symbol" << std::endl;
			exit(-1);
		}
		node = left;
	}

	if (SymbolNode* sym = dynamic_cast<SymbolNode*>(node.get())) {
		res.push_back(sym->getName());
	}
	else {
		std::cerr << "InterpretError : function arguments name must be symbol" << std::endl;
	  	exit(-1);
	}
	return res;
}

std::vector<Semantic> Interpreter::openArgumentsSE(std::shared_ptr<Node> arguments) {
	std::vector<Semantic> res;
	if (arguments == nullptr) {
		return res;
	}
	std::shared_ptr<Node> node = arguments;
	while (BinaryNode* binary = dynamic_cast<BinaryNode*>(node.get())) {
		std::shared_ptr<Node> left, right;
		binary->getNodes(left, right);
		res.push_back(action(right));
		node = left;
	}
	res.push_back(action(node));
	return res;
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
	if (_varAddress.count(name)) {
		_var[_varAddress.at(name)] = val.getNumber();
	}
	else {
		std::cerr << "InterpretError : assigned not declared variable" << std::endl;
		exit(-1);
	}
}

void Interpreter::defVar(std::string name, Semantic val) {
	if (_varAddress.count(name)) {
		std::cerr << "InterpretError : declare declared variable" << std::endl;
		exit(-1);
	}
	else {
		_varAddress.emplace(name, _varNum);
		if (_var.size() > _varNum) _var[_varNum] = val.getNumber();
		else _var.push_back(val.getNumber());
		_varNum++;
	}
}

void Interpreter::delVar(std::string name) {
	if (_varAddress.count(name)) {
		_varAddress.erase(name);
		_varNum--;
	}
	else {
		std::cerr << "InterpretError : cannot delete undefined variable" << std::endl;
		exit(-1);
	}
}

float Interpreter::getVar(std::string name) {
	if (_varAddress.count(name)) {
		return _var[_varAddress.at(name)];
	}
	else {
		std::cerr << "InterpretError : called not declared variable" << std::endl;
		exit(-1);
	}
	return 0;
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