#include "Interpreter.h"

Interpreter::Interpreter(std::string source) {
	Lexer lexer(source);  // Lexerさんに字句解析させて、
	Parser parser(lexer); // Parserさんに構文解析させて、
	_ast = parser.parse();// ASTを作ってもらう。
}

void Interpreter::interpret() {
	action(std::move(_ast));
}

Semantic Interpreter::action(std::unique_ptr<Node> node) {
	// ここ大事
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
		//列挙体はswitch文で使いやすい
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
	//getNumberで数字じゃなかったらSemanticのほうでエラーがでるのでこっちはただ計算するだけでおけ
	//以降も同じ
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