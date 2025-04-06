#pragma once

#include <iostream>
#include <string>
#include "Semantic.h"
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"

// �C���^�v���^�̃N���X
class Interpreter {
public:
	Interpreter(std::string source);
	~Interpreter() = default;

	void interpret(); // ���ߎ��s�Ƃ��Ă΂��

private:
	std::unique_ptr<Node> _ast; // ���ۖ؍\���B���s���₷��

	Semantic action(std::unique_ptr<Node> node); // �ċA�֐�

	//�֐���I�y���[�^�v�Z�Ƃ��͊֐��ŁB�킩��₷���厖�B
	void print(Semantic sem);
	Semantic plus(Semantic left, Semantic right);
	Semantic minus(Semantic left, Semantic right);
	Semantic multiply(Semantic left, Semantic right);
	Semantic division(Semantic left, Semantic right);
};