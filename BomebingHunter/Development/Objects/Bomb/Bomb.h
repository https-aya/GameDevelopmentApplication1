#pragma once
#include "../GameObject.h"

class Bomb : public GameObject
{
private:
	int animation;
	int flip_flag;

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
};

