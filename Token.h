#pragma once

#include <string>

enum class eTokenType {
	NUMBER,    // 数字
	STRING,    // 文字列
	PLUS,      // +
	MINUS,     // -
	MULTIPLY,  // *
	DIVISION,  // /
	SEMICOLON, // ;
	RPAREN,    // (
	LPAREN,    // )
	LBRACE,    // {
	RBRACE,    // }
	COMMA,     // ,
	PRINT,     // print
	ASSIGN,    // =
	VARDEF,    // var
	SYMBOL,    // 変数名・関数名
	FUNCDEF,   // func
	FUNC,      // 関数呼び出し
	END,       // 文末
	ERROR      // エラー
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