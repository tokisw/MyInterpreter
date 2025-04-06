#include <iostream>
#include <string>
#include <memory>
#include "Interpreter.h"

//プログラムを入力したら、実行結果が表示されます。
int main() {
	std::cout << "===EnterProgram===" << std::endl;
	std::string source;
	std::cin >> source;
	std::cout << "===Result===" << std::endl;
	std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(source);
	interpreter->interpret();
	return 0;
}