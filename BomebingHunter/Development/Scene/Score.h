#pragma once

#include <vector>

#define FLAME_RATE (144)

class Score
{
private:
	int score;							//�X�R�A
	int high_score;						//�n�C�X�R�A
	std::vector<int> number_image;		//�����̉摜
	std::vector<int> font_image;		//�����̉摜
	int score_digit[10];				//�X�R�A�������Ƃɕۑ�����
	int high_score_digit[10];			//�n�C�X�R�A�������Ƃɕۑ�����
	int score_digit_size;				//�X�R�A�̌��̐�
	int high_score_digit_size;			//�n�C�X�R�A�̌���
	int time_digit[2];					//���Ԃ��������Ƃɕۑ�����
	int time;							//����
	int count_time;						//���Ԃ����炷�^�C�~���O�𑪂�

public:
	//�R���X�g���N�^
	Score();
	//�f�X�g���N�^
	~Score();		

	//����������
	void Initialize();
	//�X�V����
	void Update();	
	//�`�揈��
	void Draw() const;	
	//�I��������
	void Finalize();		

	//�X�R�A�ύX����
	void SetScore(int scr);	
	//�X�R�A�擾����
	int GetScore() const;	
	//�n�C�X�R�A�ύX����
	void SetHighScore();	
	//���Ԏ擾����
	int GetTime() const;
};

