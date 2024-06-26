#pragma once

#include "../GameObject.h"
#include <vector>

class Player : public GameObject
{
private:
	std::vector<int> animation;			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	int flip_flag;				//���]�t���O

public:
	Player();
	~Player();

	virtual void Initialize() override;			//����������
	virtual void Update() override;				//�X�V����
	virtual void Draw() const override;			//�`�揈��
	virtual void Finalize() override;			//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();
};

