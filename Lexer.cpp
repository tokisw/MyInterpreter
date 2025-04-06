#include "Lexer.h"

Lexer::Lexer(std::string source)
	:_source(source), _pos(0) {}

Token Lexer::getNextToken() {
	while (_pos < _source.size()) {  // �z��̃T�C�Y�I�[�o�[�ɂ͋C��t���܂��傤�B
		char current = _source[_pos];

		if (std::isspace(current)) { // �󔒂�������
			_pos++;
			continue;
		}
		else if (std::isdigit(current)) { // ������������
			return number();
		}
		else if (std::isalpha(current)) { // �A���t�@�x�b�g��������
			return string();
		}
		else { // ���̑��F�L����������
			return sign();
		}
	}

	return Token{ eTokenType::END, 0 }; // �S�����I�������eTokenType::END��Ԃ��B
}


Token Lexer::number() {
	int start = _pos; // �L���p
	float point = true; // �����_�`�F�b�N�p
	while (_pos < _source.size() && std::isdigit(_source[_pos]) || _source[_pos] == '.') {
		if (_source[_pos] == '.') {
			if (point) { // �����_�P��
				point = false;
			}
			else { // �����_�Q��
				std::cerr << "LexerError : more than two points" << std::endl;
				exit(-1);
				// �G���[�f���ďI���B���l�����[�����B
			}
		}
		_pos++;
	}
	float value = std::stof(_source.substr(start, _pos)); 
	// substr�͕������Ԃ��̂ŁAstof�ŕ��������_���ɕϊ�
	return Token{ eTokenType::NUMBER, value };
}

Token Lexer::string() {
	int start = _pos;
	while (_pos < _source.size() && std::isalpha(_source[_pos])) {
		_pos++;
	}
	// �����܂ł͐����̎��Ɠ����B
	std::string str = _source.substr(start, _pos); // ���̕����񂪂Ȃ�Ƃ����P�ꂩ�ꍇ����
	if (str == "print") {
		return Token{ eTokenType::PRINT, 0 };
	}
	else {
		std::cerr << "LexerError : Unknown string" << std::endl;
		exit(-1);
		//����͕�������ϐ�������Ȃ��̂ŁA"print"�ȊO��������G���[�f���ďI���B���l��()
	}
	//return Token{ eTokenType::ERROR, 0 };
}

Token Lexer::sign() {
	// ����͎l�����Z�݂̂�������Ȃ����Abool�^��ǉ������"=="�Ƃ��K�v�Bswitch���͍������B
	// �����܂�܂̃v���O�����ł��B
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