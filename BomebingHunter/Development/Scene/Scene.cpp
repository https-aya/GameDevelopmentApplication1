#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyBullet.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include <math.h>

//�R���X�g���N�^
Scene::Scene() : 
	objects(), 
	Background(NULL), 
	count_time(0), 
	count_rand(0), 
	create_rand(0), 
	enemy_rand(0),
	enemy_count(0),
	high_score(0),
	time(0)
{
}

//�f�X�g���N�^
Scene::~Scene()
{
	DeleteGraph(Background);
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f),ePlayer, 0.0f);
	enemy_count = 0;
	count_time = 1;
	count_rand = 100;
	enemy_rand = 3;
	Background = LoadGraph("Resource/Images/BackGround.png");
	scores->Initialize();
	time_up->Initialize();
	time = 6000;
}

//�X�V����
void Scene::Update()
{
	if (time > 0)
	{
		time--;
		count_time++;

		//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
		for (GameObject* obj : objects)
		{
			//	Vector2D i=obj->GetScale();		
			//	if (i.x != NULL && i.y != NULL)
			//	{
			obj->Update();
			//	}
		}
		if (count_time >= count_rand)
		{
			if (enemy_count < 6)
			{
				if (create_rand == 0)
				{
					switch (enemy_rand)
					{
					case 0:
						CreateObject<Enemy>(Vector2D(600.0f, 400.0f), eBoxEnemy, 0.0f);
						break;
					case 1:
						CreateObject<Enemy>(Vector2D(600.0f, 200.0f + GetRand(100)), eFlyEnemy, 0.0f);
						break;
					case 2:
						CreateObject<Enemy>(Vector2D(600.0f, 200.0f + GetRand(100)), eHarpy, 0.0f);
						break;
					case 3:
						CreateObject<Enemy>(Vector2D(600.0f, 400.0f), eGoldEnemy, 0.0f);
						break;
					}

				}
				else
				{
					switch (enemy_rand)
					{
					case 0:
						CreateObject<Enemy>(Vector2D(40.0f, 400.0f), eBoxEnemy, 0.0f);
						break;
					case 1:
						CreateObject<Enemy>(Vector2D(40.0f, 200.0f + GetRand(100)), eFlyEnemy, 0.0f);
						break;
					case 2:
						CreateObject<Enemy>(Vector2D(40.0f, 200.0f + GetRand(100)), eHarpy, 0.0f);
						break;
					case 3:
						CreateObject<Enemy>(Vector2D(40.0f, 400.0f), eGoldEnemy, 0.0f);
						break;
					}
				}
				enemy_count++;
				create_rand = GetRand(1);
			}
			count_rand = (GetRand(1) + 1) * 100;
			enemy_rand = GetRand(3);
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
			CreateObject<Bomb>(objects[0]->GetLocation(), eBome, 0.0f);

		}
		if (InputControl::GetKey(KEY_INPUT_X))
		{
			CreateObject<Bomb>(objects[0]->GetLocation(), eBome, 0.0f);
		}
		for (int i = 0; i <= objects.size()-1; i++)
		{
			if (objects[i]->GetShotFlag() == TRUE)
			{
				Vector2D P = objects[0]->GetLocation();
				Vector2D E = objects[i]->GetLocation();
				float a = ((P.x - E.x) * (P.x - E.x) + (P.y - E.y) * (P.y - E.y));
				a = sqrtf(a);
				CreateObject<EnemyBullet>(objects[i]->GetLocation(), eEnemyBullet, ((P - E) / a));
			}
		}
		for (int i = 0; i <= objects.size()-1; i++)
		{
			if (objects[i]->GetDelete() == TRUE)
			{
				int type = objects[i]->GetType();
				if (type != 1 && type != 2 && type != 7)
				{
					enemy_count--;
				}
				objects.erase(objects.begin() + i);
			}
		}
		scores->Update(time/100);
	}
	else
	{
		scores->SetHighScore();
		time_up->Update(scores->GetScore());
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			Finalize();
			Initialize();
		}
	}

}


//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 640, 480, Background, FALSE);
	if (time > 0)
	{
		//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
		for (GameObject* obj : objects)
		{
			obj->Draw();
		}
		scores->Draw();
		DrawFormatString(300, 450, 0xffffff, "%d", scores->GetScore());
		DrawFormatString(10, 10, 0x000000, "%d", enemy_count);
	}
	else
	{
		time_up->Draw();
	}
	DrawFormatString(50, 50, 0x000000, "%d", time);
}

//�I��������
void Scene::Finalize()
{

	scores->Finalize();
	time_up->Finalize();

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
	delete scores;
	delete time_up;
}

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D diff = a->GetLocation() - b->GetLocation();

	Vector2D box_size = (a->GetScale() + b->GetScale()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		char a_type = a->GetType();
		char b_type = b->GetType();
		if (a_type != b_type)
		{
			if (((a_type == eBome || b_type == eBome) && (a_type != eEnemyBullet && b_type != eEnemyBullet)) || (a_type == ePlayer && b_type == eEnemyBullet))
			{				
				scores->SetScore(a->GetSca());
				scores->SetScore(b->GetSca());
			}
		}
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}