#pragma once

#include <iostream>
#include <string>
#include "Token.h"

//�����͊�
class Lexer {
public:
	Lexer(std::string source);
	~Lexer() = default;

	Token getNextToken(); // 1�P�ꂸ���ׂ�Token�^�̃f�[�^�Ƃ��ĕԂ�

private:
	std::string _source; // �\�[�X�R�[�h
	int _pos; // ���ݒ��ׂĂ���ꏊ:�\�[�X�R�[�h��(_pos)������
	
	Token number(); // ������������
	Token string(); // �����񂾂�����
	Token sign();   // �L����������
};