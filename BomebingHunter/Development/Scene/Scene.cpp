#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyBullet.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "../Utility/ResourceManager.h"
#include <math.h>

//コンストラクタ
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

//デストラクタ
Scene::~Scene()
{
	delete scores;
	delete time_up;
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
 	scores->Initialize();
	time_up->Initialize();
	//プレイヤーを生成する
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
		throw("背景画像が見つかりません");
	}
	for (int i = 0; i < sound.size(); i++)
	{
		if (sound[i] == -1)
		{
			throw("ゲーム中BGMが見つかりません");
		}
	}
}

//更新処理
void Scene::Update()
{
	if (scores->GetTime() > 0)
	{
		count_time++;
		if (CheckSoundMem(sound[0]) != 1)
		{
			PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP);
		}
		
		//シーンに存在するオブジェクトの更新処理
		for (GameObject* obj : objects)
		{
			obj->Update();
		}
		if (count_time >= count_rand)
		{
			//画面内で生成する敵の最大数
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
		//オブジェクト同士の当たり判定チェック
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				//当たり判定チェック処理
				HitCheckObject(objects[i], objects[j]);
			}
		}

		//zキーが押されたら爆弾を落とす
		if (InputControl::GetKeyDown(KEY_INPUT_Z))
		{
			PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
			CreateObject<Bomb>(objects[0]->GetLocation(), eBome, 0.0f);

		}

		//敵が弾を打つ
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
		//削除処理
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
		//リトライ機能
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			Finalize();
			Initialize();
		}
	}

}


//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawExtendGraph(0, 0, 640, 480, Background, FALSE);
	if (scores->GetTime() > 0)
	{
		//シーンに存在するオブジェクトの描画処理
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

//終了時処理
void Scene::Finalize()
{

	scores->Finalize();
	time_up->Finalize();

	//動的配列が秋なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の開放
	objects.clear();
	sound.clear();
	//画像の削除
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