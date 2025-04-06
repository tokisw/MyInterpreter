#pragma once

#include <iostream>

//意味値の種類を表す列挙体
enum class SemanticType {
	NONE,
	NUMBER
};

//意味値のデータを持つクラス
class Semantic {
public:
	// コンストラクタ。オーバーライドで煩わしい引数設定をへらせます。
	Semantic();
	Semantic(float number);

	SemanticType getType() const; // 意味値の種類を返す
	float getNumber() const;      // 意味値の種類が数字だった場合のみ、その値を返す

private:
	SemanticType _type;
	// 今回は浮動小数点数のみ。文字列とかも実装したらここに足していこう
	float _number;
};