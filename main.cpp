#include <iostream>
#include <string>
#include "Interpreter.h"

int main() {
	std::cout << "===EnterProgram===" << std::endl;
	std::string source;
	std::cin >> source;
	std::cout << "===Result===" << std::endl;
	Interpreter interpreter(source);
	interpreter.interpret();
	return 0;
}