#pragma once

enum class eTokenType {
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVISION,
	SEMICOLON,
	RPAREN,
	LPAREN,
	PRINT,
	END,
	ERROR
};


struct Token {
	eTokenType type;
	float value;
};