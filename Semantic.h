#pragma once

#include <iostream>

enum class SemanticType {
	NONE,
	NUMBER
};

class Semantic {
public:
	Semantic();
	Semantic(float number);

	SemanticType getType() const;
	float getNumber() const;

private:
	SemanticType _type;
	float _number;
};