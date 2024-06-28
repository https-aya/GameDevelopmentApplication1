#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/ResourceManager.h"
#include <vector>

#define D_PIVOT_CENTER		//���W�̌��_���摜�̒��S�ɂ���

enum ObjectType
{
	ePlayer,
	eBome,
	eBoxEnemy,
	eFlyEnemy,
	eHarpy,
	eGoldEnemy,
	eEnemyBullet,
};

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;			//�ʒu���
	Vector2D box_size;			//�傫��
	Vector2D direction;			//�ړ�����
	double radian;				//����
	int image;					//�`�悷��摜
	int sound;					//�Đ����鉹��
	ObjectType type;			//�v���C���[���G���𔻒f����
	bool Delete;				//�폜�t���O
	bool shot_flag;				//�G�̃V���b�g�t���O
	int score;					//���_����X�R�A
	std::vector<int> animation;			//�A�j���[�V�����摜

	ResourceManager* rm = ResourceManager::GetInstance();

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();			//����������
	virtual void Update();				//�X�V����
	virtual void Draw() const;			//�`�揈��
	virtual void Finalize();			//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);
	//�����蔻��̑傫���擾����
	Vector2D GetScale() const;
	//��ގ擾����
	int GetType() const;
	//�폜�t���O�擾����
	bool GetDelete() const;
	//�ړ������ύX����
	void SetDirection(const Vector2D& direction);
	//�ړ������擾����
	Vector2D GetDirection() const;
	//��ޕύX����
	void SetType(const ObjectType type);
	//�V���b�g�t���O�擾����
	bool GetShotFlag() const;
	//�X�R�A�擾����
	int GetScore() const;
};