#pragma once

//�P��̎�ނ�\���񋓑�
enum class eTokenType {
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVISION,
	SEMICOLON,
	RPAREN,
	LPAREN,
	PRINT,
	END,
	ERROR
};

//�P��̃f�[�^��\���\����
struct Token {
	eTokenType type;
	float value;
};