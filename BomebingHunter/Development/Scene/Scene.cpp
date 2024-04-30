#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/boxEnemy.h"
#include "../Objects/Enemy/WingEnemy.h"

//�R���X�g���N�^
Scene::Scene() : objects(), Background(NULL), counttime(),countrand(),createrand()
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
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
	CreateObject<boxEnemy>(Vector2D(600.0f, 400.0f));
	CreateObject<WingEnemy>(Vector2D(600.0f, 300.0f));
	counttime = 1;
	countrand = 1000;
	createrand = 0;
	Background = LoadGraph("Resource/Images/BackGround.png");
}

//�X�V����
void Scene::Update()
{
	counttime++;
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
	if (counttime >= countrand)
	{
		if (createrand == 0)
		{
			CreateObject<boxEnemy>(Vector2D(600.0f, 400.0f));
			CreateObject<WingEnemy>(Vector2D(600.0f, 300.0f));
		}
		else
		{
			CreateObject<boxEnemy>(Vector2D(0.0f, 400.0f));
			CreateObject<WingEnemy>(Vector2D(0.0f, 300.0f));
		}
		createrand = GetRand(1);
		countrand = GetRand(11) * 100;
		counttime = 0;
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