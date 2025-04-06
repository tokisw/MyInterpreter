#pragma once

#include <memory>
#include "Token.h"

// ASTのノードを表すクラス。
// 抽象クラスであるNodeを親としていろいろ継承させる
class Node {
public:
	~Node() = default;
	virtual void foo() {}; // 抽象クラスであることを示すため。もっといい方法あるかも？
};

//数字のデータをもつノード
class NumberNode : public Node {
public:
	explicit NumberNode(float number);
	void foo() override {};

	float getNumber() const; // 値を返します。const修飾子はガンガンつけていきましょう。

private:
	float _number;
};

//ノードのデータを一つと、オペレータのデータを持つノード。
//木構造の大事な部分。
class UnaryNode : public Node {
public:
	explicit UnaryNode(eTokenType op, std::unique_ptr<Node> node);
	void foo() override {};

	std::unique_ptr<Node> getNode(); //ノードを返します。moveするのでconstつけれない。
	eTokenType getOp() const; //オペレータを返す

private:
	eTokenType _op;
	std::unique_ptr<Node> _node;
};

//ノードのデータを二つと、オペレータのデータを持つノード
//木構造の超大事な部分。
class BinaryNode : public Node {
public:
	explicit BinaryNode(eTokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	void foo() override {};

	void getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right);
	// ↑ノードのポインタを参照渡しで受け取ります。returnでやってもよかったけど、多分こっちのが楽。
	eTokenType getOp() const; // オペレータを返す

private:
	eTokenType _op;
	std::unique_ptr<Node> _left, _right;
};