#pragma once

#include <iostream>
#include <memory>
#include "Lexer.h"
#include "Node.h"

// �\����͊�
class Parser {
public:
	Parser(Lexer lexer);
	~Parser() = default;

	std::unique_ptr<Node> parse(); // �\����͂���AST���쐬

private:
	Lexer _lexer; // �����͂��Ȃ���\����͂��܂��B���ʂȕϐ������Ȃ��Ă悭�Ȃ�܂��B
	Token _currentToken; // Lexer�ɉ�͂��Ă�������P��̃f�[�^

	void shift(eTokenType type); // Lexer����Ɏ��̒P��̉�͂�������B
								 //���@�G���[�������邽�߂�Parser���񂪎���

	// ���@�̒�`�ɏ]���� ���������[���������A�A�A
	std::unique_ptr<Node> program();
	std::unique_ptr<Node> statement();
	std::unique_ptr<Node> expression();
	std::unique_ptr<Node> term();
	std::unique_ptr<Node> factor();
};