#pragma once

#include <memory>
#include "Token.h"

// AST�̃m�[�h��\���N���X�B
// ���ۃN���X�ł���Node��e�Ƃ��Ă��낢��p��������
class Node {
public:
	~Node() = default;
	virtual void foo() {}; // ���ۃN���X�ł��邱�Ƃ��������߁B�����Ƃ������@���邩���H
};

//�����̃f�[�^�����m�[�h
class NumberNode : public Node {
public:
	explicit NumberNode(float number);
	void foo() override {};

	float getNumber() const; // �l��Ԃ��܂��Bconst�C���q�̓K���K�����Ă����܂��傤�B

private:
	float _number;
};

//�m�[�h�̃f�[�^����ƁA�I�y���[�^�̃f�[�^�����m�[�h�B
//�؍\���̑厖�ȕ����B
class UnaryNode : public Node {
public:
	explicit UnaryNode(eTokenType op, std::unique_ptr<Node> node);
	void foo() override {};

	std::unique_ptr<Node> getNode(); //�m�[�h��Ԃ��܂��Bmove����̂�const����Ȃ��B
	eTokenType getOp() const; //�I�y���[�^��Ԃ�

private:
	eTokenType _op;
	std::unique_ptr<Node> _node;
};

//�m�[�h�̃f�[�^���ƁA�I�y���[�^�̃f�[�^�����m�[�h
//�؍\���̒��厖�ȕ����B
class BinaryNode : public Node {
public:
	explicit BinaryNode(eTokenType op, std::unique_ptr<Node> left, std::unique_ptr<Node> right);
	void foo() override {};

	void getNodes(std::unique_ptr<Node>& left, std::unique_ptr<Node>& right);
	// ���m�[�h�̃|�C���^���Q�Ɠn���Ŏ󂯎��܂��Breturn�ł���Ă��悩�������ǁA�����������̂��y�B
	eTokenType getOp() const; // �I�y���[�^��Ԃ�

private:
	eTokenType _op;
	std::unique_ptr<Node> _left, _right;
};