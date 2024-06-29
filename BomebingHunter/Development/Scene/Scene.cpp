#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyBullet.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "../Utility/ResourceManager.h"
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
	sound()
{
}

//�f�X�g���N�^
Scene::~Scene()
{
	delete scores;
	delete time_up;
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
 	scores->Initialize();
	time_up->Initialize();
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f),ePlayer, 0.0f);
	std::vector<int> tmp;
	enemy_count = 0;
	count_time = 1;
	count_rand = 100;
	enemy_rand = 3;
	Background = LoadGraph("Resource/Images/BackGround.png");
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/BGM_arrows.wav");
	sound.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/pan.wav");
	sound.push_back(tmp[0]);

	if (Background == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	for (int i = 0; i < sound.size(); i++)
	{
		if (sound[i] == -1)
		{
			throw("�Q�[����BGM��������܂���");
		}
	}
}

//�X�V����
void Scene::Update()
{
	if (scores->GetTime() > 0)
	{
		count_time++;
		if (CheckSoundMem(sound[0]) != 1)
		{
			PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP);
		}
		
		//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
		for (GameObject* obj : objects)
		{
			obj->Update();
		}
		if (count_time >= count_rand)
		{
			//��ʓ��Ő�������G�̍ő吔
			if (enemy_count < MAX_ENEMY)
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

		//z�L�[�������ꂽ�甚�e�𗎂Ƃ�
		if (InputControl::GetKeyDown(KEY_INPUT_Z))
		{
			PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
			CreateObject<Bomb>(objects[0]->GetLocation(), eBome, 0.0f);

		}

		//�G���e��ł�
		for (int i = 0; i <= objects.size()-1; i++)
		{
			if (objects[i]->GetShotFlag() == TRUE)
			{
				Vector2D P = objects[0]->GetLocation();
				Vector2D E = objects[i]->GetLocation();
				float a = pow((P.x - E.x),2) + pow((P.y - E.y),2);
				a = sqrtf(a);
				CreateObject<EnemyBullet>(objects[i]->GetLocation(), eEnemyBullet, (P - E) / a);
			}
		}
		//�폜����
		for (int i = 0; i <= objects.size()-1; i++)
		{
			if (objects[i]->GetDelete() == TRUE)
			{
				int type = objects[i]->GetType();
				if (type != ePlayer && type != eBome && type != eEnemyBullet)
				{
					enemy_count--;
				}
				objects.erase(objects.begin() + i);
			}
		}
		scores->Update();
	}
	else
	{
		StopSoundMem(sound[0]);
		scores->SetHighScore();
		time_up->Update(scores->GetScore());
		//���g���C�@�\
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
	if (scores->GetTime() > 0)
	{
		//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
		for (GameObject* obj : objects)
		{
			obj->Draw();
		}
		scores->Draw();
	}
	else
	{
		time_up->Draw();
	}
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
	sound.clear();
	//�摜�̍폜
	DeleteGraph(Background);
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
				scores->SetScore(a->GetScore());
				scores->SetScore(b->GetScore());
			}
		}
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}