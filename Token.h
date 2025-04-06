#pragma once

//単語の種類を表す列挙体
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

//単語のデータを表す構造体
struct Token {
	eTokenType type;
	float value;
};