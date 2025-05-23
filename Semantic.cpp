#include "Semantic.h"

Semantic::Semantic()
	:_type(SemanticType::NONE), _number(0), _string("") {}

Semantic::Semantic(float number) 
	:_type(SemanticType::NUMBER), _number(number), _string("") {}

Semantic::Semantic(std::string string)
	:_type(SemanticType::STRING), _number(0), _string(string) {}

Semantic::Semantic(std::string name, float val)
	:_type(SemanticType::VARIABLE), _string(name), _number(val) {}

SemanticType Semantic::getType() const {
	return _type;
}

float Semantic::getNumber() const {
	if (_type == SemanticType::NUMBER || _type == SemanticType::VARIABLE) {
		return _number;
	}
	else {
		std::cerr << "SemanticError : not number" << std::endl;
		exit(-1);
	}
	return 0.f;
}

std::string Semantic::getString() const {
	if (_type == SemanticType::STRING || _type == SemanticType::VARIABLE) {
		return _string;
	}
	else {
		std::cerr << "SemanticError : not string" << std::endl;
		exit(-1);
	}
	return "";
}