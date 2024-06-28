#pragma once

#include "../GameObject.h"
#include "../../Scene/FlyText.h"

class Enemy : public GameObject
{
private:
	int animation_count;				//�A�j���[�V��������
	int max_animation;					//�A�j���[�V�����̍ő吔
	int anime_time;						//�ǂ̃A�j���[�V������
	int shot_count;						//�G�e��łԊu
	int shot_rand;						//�G�e�̊Ԋu�������_���ɂ���
	int alpha;							//�摜�̓����x
	bool blend_flag;					//�������t���O
	Vector2D anim_location;

	FlyText* fly_text = new FlyText;

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

