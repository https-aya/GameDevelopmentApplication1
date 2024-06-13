#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"
#include "Score.h"
#include "TimeUp.h"

class Scene
{
private:
	std::vector<GameObject*> objects;
private:
	//�w�i�摜
	int Background;
	int count_time;			//�����Ԋu�̃J�E���g
	int count_rand;			//�����_���Ő����Ԋu�����߂�
	int create_rand;		//�����ʒu�������_���Ō��߂�
	int enemy_rand;			//��������G�������_���Ō��߂�
	int enemy_count;		//�G�̐�����
	int high_score;
	int time;
	Score* scores = new Score;
	TimeUp* time_up = new TimeUp;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//�����蔻��`�F�b�N
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location,int enemy_type,const Vector2D& direction)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//��ނ̐ݒ�
		new_object->SetType(enemy_type);

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�ړ������̐ݒ�
		new_object->SetDirection(direction);

		//����������
		new_object->Initialize();

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};

