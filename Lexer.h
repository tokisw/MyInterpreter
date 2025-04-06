#pragma once

#include <iostream>
#include <string>
#include "Token.h"

//字句解析器
class Lexer {
public:
	Lexer(std::string source);
	~Lexer() = default;

	Token getNextToken(); // 1単語ずつ調べてToken型のデータとして返す

private:
	std::string _source; // ソースコード
	int _pos; // 現在調べている場所:ソースコードの(_pos)文字目
	
	Token number(); // 数字だった時
	Token string(); // 文字列だった時
	Token sign();   // 記号だった時
};