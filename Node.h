#pragma once

#include <memory>
#include "Token.h"

class Node {
public:
	~Node() = default;
	virtual void foo() {};
};


class NumberNode : public Node {
public:
	explicit NumberNode(float number);
	void foo() override {};

	float getNumber() const;

private:
	float _number;
};


class UnaryNode : public Node {
public:
	explicit UnaryNode(eTokenType op, std::unique_ptr<Node>&& node);
	void foo() override {};

	std::unique_ptr<Node> getNode();
	eTokenType getOp() const;

private:
	eTokenType _op;
	std::unique_ptr<Node> _node;
};


class BinaryNode : public Node {
public:
	explicit BinaryNode(eTokenType op, std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right);
	void foo() override {};

	void getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right);
	eTokenType getOp() const;

private:
	eTokenType _op;
	std::unique_ptr<Node> _left, _right;
};