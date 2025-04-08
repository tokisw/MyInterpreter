#include "Token.h"

Token::Token(eTokenType type)
	: _type(type), _number(0.f), _string("") {}

Token::Token(float number)
	: _number(number), _type(eTokenType::NUMBER), _string("") {}

Token::Token(std::string string)
	: _string(string), _type(eTokenType::STRING), _number(0.f) {}

eTokenType Token::getType() const {
	return _type;
}

float Token::getNumber() const {
	return _number;
}

std::string Token::getString() const {
	return _string;
}