#pragma once

#include <iostream>
#include <memory>
#include "Lexer.h"
#include "Node.h"

// 構文解析器
class Parser {
public:
	Parser(Lexer lexer);
	~Parser() = default;

	std::unique_ptr<Node> parse(); // 構文解析してASTを作成

private:
	Lexer _lexer; // 字句解析しながら構文解析します。無駄な変数を作らなくてよくなります。
	Token _currentToken; // Lexerに解析してもらった単語のデータ

	void shift(eTokenType type); // Lexerさんに次の単語の解析をさせる。
								 //文法エラーを見つけるためにParserさんが持つ

	// 文法の定義に従おう 自分がルールだった、、、
	std::unique_ptr<Node> program();
	std::unique_ptr<Node> statement();
	std::unique_ptr<Node> expression();
	std::unique_ptr<Node> term();
	std::unique_ptr<Node> factor();
};