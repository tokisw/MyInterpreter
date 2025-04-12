#pragma once

#include <string>

enum class eTokenType {
	NUMBER,
	STRING,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVISION,
	SEMICOLON,
	RPAREN,
	LPAREN,
	PRINT,
	ASSIGN,
	VARDEF,
	VARNAME,
	END,
	ERROR
};

class Token {
public:
	Token(eTokenType type);
	Token(eTokenType type, std::string name);
	Token(float number);
	Token(std::string string);
	~Token() = default;

	eTokenType getType() const;
	float getNumber() const;
	std::string getString() const;

private:
	eTokenType _type;
	float _number;
	std::string _string;
};