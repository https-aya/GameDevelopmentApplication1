#pragma once

#include "../GameObject.h"

class Enemy : public GameObject
{
private:
	int animation[5];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	int max_animation;			//�A�j���[�V�����̍ő吔
	int anime_time;				//�ǂ̃A�j���[�V������
	int shot_count;
	int shot_rand;

public:
	Enemy();
	~Enemy();

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

