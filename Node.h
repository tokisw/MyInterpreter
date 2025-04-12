#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "Token.h"

class Node {
public:
	~Node() = default;
	virtual void show(int index) {};
};

class NumberNode : public Node {
public:
	explicit NumberNode(float number);
	void show(int index) override;

	float getNumber() const;

private:
	float _number;
};

class StringNode : public Node {
public:
	explicit StringNode(std::string str);
	void show(int index) override;

	std::string getString() const;

private:
	std::string _string;
};

class UnaryNode : public Node {
public:
	explicit UnaryNode(eTokenType op, std::unique_ptr<Node> node);
	void show(int index) override;

	std::unique_ptr<Node> getNode();
	eTokenType getOp() const;

private:
	eTokenType _op;
	std::unique_ptr<Node> _node;
};

class BinaryNode : public Node {
public:
	explicit BinaryNode(eTokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	void show(int index) override;

	void getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right);
	eTokenType getOp() const;

private:
	eTokenType _op;
	std::unique_ptr<Node> _left, _right;
};

class VariableNode : public Node {
public:
	explicit VariableNode(std::string name);
	void show(int index) override;

	std::string getName() const;

private:
	std::string _name;
};