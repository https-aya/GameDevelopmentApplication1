#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

class FlyText
{
private:
	std::vector<int> number_image;	//�����̉摜
	int fly_text_digit[3];			//�����������Ƃɕۑ�
	int digit_size;					//����
	int score;						//�\������X�R�A

public:
	//�R���X�g���N�^
	FlyText();
	//�f�X�g���N�^
	~FlyText();

	//����������
	void Initialize();
	//�`�揈��
	//@param location:�`�悷����W
	//@param sco:�`�悷��_��
	void Draw(Vector2D location) const;
	//�I��������
	void Finalize();
	//�_���̕ύX����
	void SetFlyText(int ft);

};

