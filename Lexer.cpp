#include "Lexer.h"

Lexer::Lexer(std::string source)
	:_source(source), _pos(0) {}

Token Lexer::getNextToken() {
	while (_pos < _source.size()) {  // 配列のサイズオーバーには気を付けましょう。
		char current = _source[_pos];

		if (std::isspace(current)) { // 空白だった時
			_pos++;
			continue;
		}
		else if (std::isdigit(current)) { // 数字だった時
			return number();
		}
		else if (std::isalpha(current)) { // アルファベットだった時
			return string();
		}
		else { // その他：記号だった時
			return sign();
		}
	}

	return Token{ eTokenType::END, 0 }; // 全部見終わったらeTokenType::ENDを返す。
}


Token Lexer::number() {
	int start = _pos; // 記憶用
	float point = true; // 小数点チェック用
	while (_pos < _source.size() && std::isdigit(_source[_pos]) || _source[_pos] == '.') {
		if (_source[_pos] == '.') {
			if (point) { // 小数点１個目
				point = false;
			}
			else { // 小数点２個目
				std::cerr << "LexerError : more than two points" << std::endl;
				exit(-1);
				// エラー吐いて終了。俺様がルールだ。
			}
		}
		_pos++;
	}
	float value = std::stof(_source.substr(start, _pos)); 
	// substrは文字列を返すので、stofで浮動小数点数に変換
	return Token{ eTokenType::NUMBER, value };
}

Token Lexer::string() {
	int start = _pos;
	while (_pos < _source.size() && std::isalpha(_source[_pos])) {
		_pos++;
	}
	// ここまでは数字の時と同じ。
	std::string str = _source.substr(start, _pos); // その文字列がなんという単語か場合分け
	if (str == "print") {
		return Token{ eTokenType::PRINT, 0 };
	}
	else {
		std::cerr << "LexerError : Unknown string" << std::endl;
		exit(-1);
		//今回は文字列も変数も扱わないので、"print"以外だったらエラー吐いて終了。俺様が()
	}
	//return Token{ eTokenType::ERROR, 0 };
}

Token Lexer::sign() {
	// 今回は四則演算のみだから問題ないが、bool型を追加すると"=="とか必要。switch文は今回限定。
	// 見たまんまのプログラムです。
	switch (_source[_pos]) {
		case '+': _pos++; return Token{ eTokenType::PLUS, 0 };
		case '-': _pos++; return Token{ eTokenType::MINUS, 0 };
		case '*': _pos++; return Token{ eTokenType::MULTIPLY, 0 };
		case '/': _pos++; return Token{ eTokenType::DIVISION, 0 };
		case '(': _pos++; return Token{ eTokenType::LPAREN, 0 };
		case ')': _pos++; return Token{ eTokenType::RPAREN, 0 };
		case ';': _pos++; return Token{ eTokenType::SEMICOLON, 0 };
		default: std::cerr << "LexerError : Unknown sign" << std::endl; exit(-1);
	}
	return Token{ eTokenType::ERROR, 0 };
}