#include "Semantic.h"

// �ς킵�������Ƃ́ASemanticType�̂��ƁB
// �����ɂ���ĈӖ��l�̎�ނ͈�Ɍ��܂�B
Semantic::Semantic()
	:_type(SemanticType::NONE), _number(0) {}

Semantic::Semantic(float number) 
	:_type(SemanticType::NUMBER), _number(number) {}

SemanticType Semantic::getType() const {
	return _type;
}

float Semantic::getNumber() const {
	if (_type == SemanticType::NUMBER) {
		return _number;
	}
	else {
		std::cerr << "ExpressionError : cannot calculate non_number" << std::endl;
		exit(-1);
		//��������Ȃ��̂�getNumber()���ꂽ�炻��͕��@�G���[�B�I�����܂��傤
	}
	return 0.f;
}