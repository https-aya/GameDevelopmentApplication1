#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"

//�R���X�g���N�^
Scene::Scene() : objects(), Background(NULL), count_time(),count_rand(),create_rand(),count_bome()
{
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f),1);
	CreateObject<Enemy>(Vector2D(600.0f, 400.0f),6);
	CreateObject<Enemy>(Vector2D(600.0f, 300.0f),5);
	count_time = 1;
	count_rand = 1000;
	create_rand = 0;
	count_bome = 0;
	Background = LoadGraph("Resource/Images/BackGround.png");
}

//�X�V����
void Scene::Update()
{
	count_time++;
	count_bome--;

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		Vector2D i=obj->GetScale();		
		if (i.x != NULL && i.y != NULL)
		{
			obj->Update();
		}
	}
	if (count_time >= count_rand)
	{
		if (create_rand == 0)
		{
			CreateObject<Enemy>(Vector2D(600.0f, 400.0f),6);
			CreateObject<Enemy>(Vector2D(600.0f, 300.0f),5);
		}
		else
		{
			CreateObject<Enemy>(Vector2D(0.0f, 400.0f),6);
			CreateObject<Enemy>(Vector2D(0.0f, 300.0f),5);
		}
		create_rand = GetRand(1);
		count_rand = GetRand(11) * 100;
		count_time = 0;
	}
	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		if (count_bome <= 0)
		{
			CreateObject<Bomb>(objects[0]->GetLocation(), 2);
			count_bome = 300;
		}
	}
	if (count_bome <= 0)
	{
		count_bome = 0;
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 640, 480, Background, FALSE);
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	DrawFormatString(10, 10, 0x000000, "%d", count_bome);
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪏H�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̊J��
	objects.clear();
}

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D diff = a->GetLocation() - b->GetLocation();

	Vector2D box_size = (a->GetScale() + b->GetScale()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		if ((a->GetType() == 2 || b->GetType() == 2) && (a->GetType() != 1 && b->GetType() != 1))
		{
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
}