#pragma once

#include "../GameObject.h"
#include <vector>

class EnemyBullet : public GameObject
{
private:
	std::vector<int> animation;		//�A�j���[�V�����摜
	bool anime_flag;		//�A�j���[�V�������邩�ǂ���
	int anime_count;		//�A�j���[�V��������
	int anime_num;			//�A�j���[�V�����ԍ�

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V�����Ǘ�
	void AnimeControl();

};

