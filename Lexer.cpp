#include "Lexer.h"

Lexer::Lexer(std::string source)
	:_source(source), _pos(0) {}

Token Lexer::getNextToken() {
	while (_pos < _source.size()) {
		char current = _source[_pos];

		if (std::isspace(current)) {
			++_pos;
			continue;
		}
		else if (std::isdigit(current)) {
			return number();
		}
		else if (std::isalpha(current)) {
			return symbol();
		}
		else if (current == '"') {
			return string();
		}
		else {
			return sign();
		}
	}

	return Token(eTokenType::END);
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
				std::cerr << "LexerError : more than two points" << std::endl;
				exit(-1);
			}
		}
		_pos++;
	}
	float value = std::stof(_source.substr(start, _pos-start));
	return Token(value);
}

Token Lexer::string() {
	_pos++;
	int start = _pos;
	while (_pos < _source.size() && _source[_pos] != '"') {
		_pos++;
	}
	if (_pos == _source.size() - 1 && _source[_pos] != '"') {
		std::cerr << "SyntaxError : must be astarisc" << std::endl;
		exit(-1);
	}
	std::string str = _source.substr(start, _pos-start);
	_pos++;
	return Token(str);
}

Token Lexer::symbol() {
	int start = _pos;
	while (_pos < _source.size() && std::isalpha(_source[_pos])) {
		_pos++;
	}
	std::string sym = _source.substr(start, _pos-start);
	if (sym == "print") {
		return Token(eTokenType::PRINT);
	}
	else if (sym == "var") {
		return Token(eTokenType::VARDEF);
	}
	else {
		return Token(eTokenType::VARNAME, sym);
	}
	return Token(eTokenType::ERROR);
}

Token Lexer::sign() {
	switch (_source[_pos]) {
		case '+': _pos++; return Token(eTokenType::PLUS);
		case '-': _pos++; return Token(eTokenType::MINUS);
		case '*': _pos++; return Token(eTokenType::MULTIPLY);
		case '/': _pos++; return Token(eTokenType::DIVISION);
		case '(': _pos++; return Token(eTokenType::LPAREN);
		case ')': _pos++; return Token(eTokenType::RPAREN);
		case ';': _pos++; return Token(eTokenType::SEMICOLON);
		case '=': _pos++; return Token(eTokenType::ASSIGN);
		default: std::cerr << "LexerError : Unknown sign" << std::endl; exit(-1);
	}
	return Token(eTokenType::ERROR);
}