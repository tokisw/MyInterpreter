#pragma once

#include <iostream>
#include <string>

enum class SemanticType {
	NONE,
	NUMBER,
	STRING
};

class Semantic {
public:
	Semantic();
	Semantic(float number);
	Semantic(std::string string);

	SemanticType getType() const;
	float getNumber() const;
	std::string getString() const;

private:
	SemanticType _type;
	float _number;
	std::string _string;
};