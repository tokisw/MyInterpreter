#pragma once

#include <iostream>
#include <string>
#include "Semantic.h"
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"

// インタプリタのクラス
class Interpreter {
public:
	Interpreter(std::string source);
	~Interpreter() = default;

	void interpret(); // 解釈実行とも呼ばれる

private:
	std::unique_ptr<Node> _ast; // 抽象木構造。実行しやすい

	Semantic action(std::unique_ptr<Node> node); // 再帰関数

	//関数やオペレータ計算とかは関数で。わかりやすさ大事。
	void print(Semantic sem);
	Semantic plus(Semantic left, Semantic right);
	Semantic minus(Semantic left, Semantic right);
	Semantic multiply(Semantic left, Semantic right);
	Semantic division(Semantic left, Semantic right);
};