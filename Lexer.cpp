#include "Lexer.h"

Lexer::Lexer(std::string source)
	:_source(source), _pos(0) {}

Token Lexer::getNextToken() {

	while (_pos < _source.size()) {
		if (std::isdigit(_source[_pos])) {
			return number();
		}
		else if (std::isalpha(_source[_pos])) {
			return string();
		}
		else {
			return sign();
		}
	}

	return Token{ eTokenType::END, 0 };
}


Token Lexer::number() {
	int start = _pos;
	float point = true;
	while (_pos < _source.size() && std::isdigit(_source[_pos]) || _source[_pos] == '.') {
		if (_source[_pos] == '.') {
			if (point) {
				point = false;
			}
			else {
				std::cerr << "NumberError : more than do" << std::endl;
				break;
			}
		}
		_pos++;
	}
	float value = std::stof(_source.substr(start, _pos));
	return Token{ eTokenType::NUMBER, value };
}

Token Lexer::string() {
	int start = _pos;
	while (_pos < _source.size() && std::isalpha(_source[_pos])) {
		_pos++;
	}
	std::string str = _source.substr(start, _pos);
	if (str == "print") {
		return Token{ eTokenType::PRINT, 0 };
	}
	else {
		std::cerr << "StringError : Unknown string" << std::endl;
	}
	return Token{ eTokenType::ERROR, 0 };
}

Token Lexer::sign() {
	int start = _pos;
	while (_pos < _source.size() && !std::isalpha(_source[_pos]) && !std::isdigit(_source[_pos])) {
		_pos++;
	}
	std::string sig = _source.substr(start, _pos);
	if (sig == "+") return Token{ eTokenType::PLUS, 0 };
	else if (sig == "-") return Token{ eTokenType::MINUS, 0 };
	else if (sig == "*") return Token{ eTokenType::MULTIPLY, 0 };
	else if (sig == "/") return Token{ eTokenType::DIVISION, 0 };
	else if (sig == "(") return Token{ eTokenType::LPAREN, 0 };
	else if (sig == ")") return Token{ eTokenType::RPAREN, 0 };
	else if (sig == ";") return Token{ eTokenType::SEMICOLON, 0 };
	else std::cerr << "SignError : Unknown sign" << std::endl;
	return Token{ eTokenType::ERROR, 0 };
}