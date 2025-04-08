#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Interpreter.h"

int main() {
	std::cout << "===Program===" << std::endl;
	std::string source = "";
	{
		std::ifstream file("Program.txt");
		std::string line;
		while (std::getline(file, line)) {
			source += line;
			std::cout << line << std::endl;
		}
	}
	std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>(source);
	std::cout << "===Result===" << std::endl;
	interpreter->interpret();
	return 0;
}