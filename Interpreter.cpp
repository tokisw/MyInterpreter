#include "Interpreter.h"

Interpreter::Interpreter(std::string source) {
	Lexer lexer(source);  // Lexer����Ɏ����͂����āA
	Parser parser(lexer); // Parser����ɍ\����͂����āA
	_ast = parser.parse();// AST������Ă��炤�B
}

void Interpreter::interpret() {
	action(std::move(_ast));
}

Semantic Interpreter::action(std::unique_ptr<Node> node) {
	// �����厖
	if (NumberNode* num = dynamic_cast<NumberNode*>(node.get())) {
		return Semantic(num->getNumber());
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
		//�񋓑̂�switch���Ŏg���₷��
		switch (binary->getOp()) {
			case eTokenType::PLUS: return plus(left, right);
			case eTokenType::MINUS: return minus(left, right);
			case eTokenType::MULTIPLY: return multiply(left, right);
			case eTokenType::DIVISION: return division(left, right);
			case eTokenType::SEMICOLON: return Semantic();
			default: std::cerr << "InterpreterError : unknwon binary token" << std::endl; exit(-1);
		}
	}
	return Semantic();
}

void Interpreter::print(Semantic sem) {
	if (sem.getType() == SemanticType::NUMBER) {
		std::cout << sem.getNumber() << std::endl;
	}
	else {
		std::cerr << "PrintError : connot print non-number" << std::endl;
		exit(-1);
	}
}

Semantic Interpreter::plus(Semantic left, Semantic right) {
	//getNumber�Ő�������Ȃ�������Semantic�̂ق��ŃG���[���ł�̂ł������͂����v�Z���邾���ł���
	//�ȍ~������
	return left.getNumber() + right.getNumber();
}

Semantic Interpreter::minus(Semantic left, Semantic right) {
	return left.getNumber() - right.getNumber();
}

Semantic Interpreter::multiply(Semantic left, Semantic right) {
	return left.getNumber() * right.getNumber();
}

Semantic Interpreter::division(Semantic left, Semantic right) {
	return left.getNumber() / right.getNumber();
}