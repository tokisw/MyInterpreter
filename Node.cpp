#include "Node.h"

NumberNode::NumberNode(float number)
	:_number(number) {}

float NumberNode::getNumber() const{
	return _number;
}


UnaryNode::UnaryNode(eTokenType op, std::unique_ptr<Node> node)
	:_op(op), _node(std::move(node)) {}

std::unique_ptr<Node> UnaryNode::getNode() {
	return std::move(_node);
}

eTokenType UnaryNode::getOp() const {
	return _op;
}


BinaryNode::BinaryNode(eTokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
	:_op(op), _left(std::move(left)), _right(std::move(right)) {} // move í¥ëÂéñÅI

void BinaryNode::getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right) {
	left = std::move(_left);
	right = std::move(_right);
	//move ëÂéñÇæÇÊÇŸÇÒÇ∆Ç…
}

eTokenType BinaryNode::getOp() const {
	return _op;
}