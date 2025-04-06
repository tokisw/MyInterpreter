#include "Semantic.h"

// 煩わしい引数とは、SemanticTypeのこと。
// 引数によって意味値の種類は一つに決まる。
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
		//数字じゃないのにgetNumber()されたらそれは文法エラー。終了しましょう
	}
	return 0.f;
}