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


UnaryNode::UnaryNode(eTokenType op, std::shared_ptr<Node> node)
	:_op(op), _node(node) {}

std::shared_ptr<Node> UnaryNode::getNode() {
	return _node;
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


BinaryNode::BinaryNode(eTokenType op, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
	:_op(op), _left(left), _right(right) {}

void BinaryNode::getNodes(std::shared_ptr<Node>& left, std::shared_ptr<Node>& right) {
	left = _left;
	right = _right;
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
		case eTokenType::COMMA: c = ","; break;
		case eTokenType::FUNC: c = "callFunc"; break;
		default: c = "error"; break;
	}
	std::cout << a << "Binary(" << c << ")\n";
	if (_left != nullptr) _left->show(index + 4);
	if (_right != nullptr) _right->show(index + 4);
}


TernaryNode::TernaryNode(eTokenType op, std::shared_ptr<Node> left, std::shared_ptr<Node> center, std::shared_ptr<Node> right)
	:_op(op), _left(left), _right(right), _center(center) {}

void TernaryNode::getNodes(std::shared_ptr<Node>& left, std::shared_ptr<Node>& center, std::shared_ptr<Node>& right) {
	left = _left;
	center = _center;
	right = _right;
}

eTokenType TernaryNode::getOp() const {
	return _op;
}

void TernaryNode::show(int index) {
	std::string a(index, ' ');
	std::string c = "";
	switch (_op) {
		case eTokenType::FUNCDEF: c = "FUNC"; break;
		default: c = "error"; break;
	}
	std::cout << a << "Ternary(" << c << ")\n";
	if (_left != nullptr) _left->show(index + 4);
	if (_center != nullptr) _center->show(index + 4);
	if (_right != nullptr) _right->show(index + 4);
}

SymbolNode::SymbolNode(std::string name)
	:_name(name) {}

std::string SymbolNode::getName() const {
	return _name;
}

void SymbolNode::show(int index) {
	std::string a(index, ' ');
	std::cout << a << "Symbol(" << _name << ")\n";
}