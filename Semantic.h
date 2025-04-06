#pragma once

#include <iostream>

//�Ӗ��l�̎�ނ�\���񋓑�
enum class SemanticType {
	NONE,
	NUMBER
};

//�Ӗ��l�̃f�[�^�����N���X
class Semantic {
public:
	// �R���X�g���N�^�B�I�[�o�[���C�h�Ŕς킵�������ݒ���ւ点�܂��B
	Semantic();
	Semantic(float number);

	SemanticType getType() const; // �Ӗ��l�̎�ނ�Ԃ�
	float getNumber() const;      // �Ӗ��l�̎�ނ������������ꍇ�̂݁A���̒l��Ԃ�

private:
	SemanticType _type;
	// ����͕��������_���̂݁B������Ƃ������������炱���ɑ����Ă�����
	float _number;
};