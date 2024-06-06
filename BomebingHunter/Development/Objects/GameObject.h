#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//���W�̌��_���摜�̒��S�ɂ���

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
	int type;					//�v���C���[���G���𔻒f����
	bool Delete;				//�폜�t���O
	bool shot_flag;				//�G�̃V���b�g�t���O
	int sca;					//�l���ł���X�R�A

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
	//��ޕύX����
	void SetType(const int type);
	//�V���b�g�t���O�擾����
	bool GetShotFlag() const;
	//�X�R�A�擾����
	int GetSca() const;
};