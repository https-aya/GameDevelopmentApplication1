#pragma once

#include <vector>

class TimeUp
{
private:
	std::vector<int> image;			//�]���̉摜
	int draw;						//�\������摜
	int count;						//�摜�؂�ւ��p�̃J�E���g

public:
	//�R���X�g���N�^
	TimeUp();
	//�f�X�g���N�^
	~TimeUp();

	//����������
	void Initialize();
	//�X�V�����i�Q�b�g�����X�R�A�ŕ\������摜��ύX����j
	void Update(int sco);
	//�`�揈��
	void Draw() const;
	//�I��������
	void Finalize();
};

