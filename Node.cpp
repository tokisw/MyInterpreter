#include "Node.h"

NumberNode::NumberNode(float number)
	:_number(number) {}

float NumberNode::getNumber() const{
	return _number;
}

void NumberNode::show(int index) {
	std::string a(index, ' ');
	std::cout << a << "Number(" << _number << ")\n";
}


StringNode::StringNode(std::string str)
	:_string(str) {}

std::string StringNode::getString() const {
	return _string;
}

void StringNode::show(int index) {
	std::string a(index, ' ');
	std::cout << a << "String(" << _string << ")\n";
}


UnaryNode::UnaryNode(eTokenType op, std::unique_ptr<Node> node)
	:_op(op), _node(std::move(node)) {}

std::unique_ptr<Node> UnaryNode::getNode() {
	return std::move(_node);
}

eTokenType UnaryNode::getOp() const {
	return _op;
}

void UnaryNode::show(int index) {
	std::string a(index, ' ');
	std::string c = "";
	switch (_op) {
		case eTokenType::PRINT: c = "print"; break;
		default: c = "error"; break;
	}
	std::cout << a << "Unary(" << c << ")\n";
	_node->show(index + 4);
}


BinaryNode::BinaryNode(eTokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
	:_op(op), _left(std::move(left)), _right(std::move(right)) {}

void BinaryNode::getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right) {
	left = std::move(_left);
	right = std::move(_right);
}

eTokenType BinaryNode::getOp() const {
	return _op;
}

void BinaryNode::show(int index) {
	std::string a(index, ' ');
	std::string c = "";
	switch (_op) {
		case eTokenType::PLUS: c = "+"; break;
		case eTokenType::MINUS: c = "-"; break;
		case eTokenType::MULTIPLY: c = "*"; break;
		case eTokenType::DIVISION: c = "/"; break;
		case eTokenType::ASSIGN: c = "="; break;
		case eTokenType::SEMICOLON: c = ";"; break;
		case eTokenType::VARDEF: c = "VAR"; break;
		default: c = "error"; break;
	}
	std::cout << a << "Binary(" << c << ")\n";
	_left->show(index + 4);
	_right->show(index + 4);
}


VariableNode::VariableNode(std::string name)
	:_name(name) {}

std::string VariableNode::getName() const {
	return _name;
}

void VariableNode::show(int index) {
	std::string a(index, ' ');
	std::cout << a << "Variable(" << _name << ")\n";
}