#include "Interpreter.h"

Interpreter::Interpreter(std::string source) {
	Lexer lexer(source);
	Parser parser(lexer);
	_ast = parser.parse();
}

void Interpreter::interpret() {
	action(std::move(_ast));
}

Semantic Interpreter::action(std::unique_ptr<Node> node) {
	if (NumberNode* num = dynamic_cast<NumberNode*>(node.get())) {
		return Semantic(num->getNumber());
	}
	if (StringNode* str = dynamic_cast<StringNode*>(node.get())) {
		return Semantic(str->getString());
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
		default:
			std::cerr << "InterpretError : print argument must be number or string" << std::endl;
			exit(-1);
			break;
	}
}

Semantic Interpreter::plus(Semantic left, Semantic right) {
	if (left.getType() == right.getType()) {
		switch (left.getType()) {
			case SemanticType::STRING: return left.getString() + right.getString();
			case SemanticType::NUMBER: return left.getNumber() + right.getNumber();
			default: 
				std::cerr << "InterpretError : plus argument must be string or number" << std::endl;
				exit(-1);
		}
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::minus(Semantic left, Semantic right) {
	if (left.getType() == right.getType()) {
		switch (left.getType()) {
		case SemanticType::NUMBER: return left.getNumber() - right.getNumber();
		default:
			std::cerr << "InterpretError : minus argument must be number" << std::endl;
			exit(-1);
		}
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::multiply(Semantic left, Semantic right) {
	if (left.getType() == right.getType()) {
		switch (left.getType()) {
		case SemanticType::NUMBER: return left.getNumber() * right.getNumber();
		default:
			std::cerr << "InterpretError : multiply argument must be number" << std::endl;
			exit(-1);
		}
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}

Semantic Interpreter::division(Semantic left, Semantic right) {
	if (left.getType() == right.getType()) {
		switch (left.getType()) {
		case SemanticType::NUMBER: return left.getNumber() / right.getNumber();
		default:
			std::cerr << "InterpretError : division argument must be number" << std::endl;
			exit(-1);
		}
	}
	else {
		std::cerr << "InterpretError : left argument type must be same as right argument type" << std::endl;
		exit(-1);
	}
	return Semantic();
}