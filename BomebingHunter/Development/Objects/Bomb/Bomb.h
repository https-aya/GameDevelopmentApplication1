#pragma once

#include "../GameObject.h"

class Bomb : public GameObject
{
private:
	int sound;	//����
	int anime_count;	//�A�j���[�V��������
	int anime_num;		//�摜�̔ԍ�
	bool anime_flag;	//�A�j���[�V�������邩�ǂ���
	Vector2D anim_location;	//�A�j���[�V�������̍��W

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;			//����������
	virtual void Update() override;				//�X�V����
	virtual void Draw() const override;			//�`�揈��
	virtual void Finalize() override;			//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V�����Ǘ�
	void AnimeControl();
};

