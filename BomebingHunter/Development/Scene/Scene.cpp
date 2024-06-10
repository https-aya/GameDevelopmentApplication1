#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyBullet.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "Score.h"

//コンストラクタ
Scene::Scene() : 
	objects(), 
	Background(NULL), 
	count_time(0), 
	count_rand(0), 
	create_rand(0), 
	enemy_rand(0),
	enemy_count(0),
	score(0),
	high_score(0)
{
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f),2, 0.0f);
	count_time = 1;
	count_rand = 100;
	enemy_rand = 3;
	Background = LoadGraph("Resource/Images/BackGround.png");
	scores->Initialize();
}

//更新処理
void Scene::Update()
{
	count_time++;
	
	//シーンに存在するオブジェクトの更新処理
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
				case 3:
					CreateObject<Enemy>(Vector2D(600.0f, 400.0f), enemy_rand, 0.0f);
					break;
				case 4:
					CreateObject<Enemy>(Vector2D(600.0f, 300.0f), enemy_rand, 0.0f);
					break;
				case 5:
					CreateObject<Enemy>(Vector2D(600.0f, 300.0f), enemy_rand, 0.0f);
					break;
				case 6:
					CreateObject<Enemy>(Vector2D(600.0f, 400.0f), enemy_rand, 0.0f);
					break;
				}

			}
			else
			{
				switch (enemy_rand)
				{
				case 3:
					CreateObject<Enemy>(Vector2D(40.0f, 400.0f), enemy_rand, 0.0f);
					break;
				case 4:
					CreateObject<Enemy>(Vector2D(40.0f, 300.0f), enemy_rand, 0.0f);
					break;
				case 5:
					CreateObject<Enemy>(Vector2D(40.0f, 300.0f), enemy_rand, 0.0f);
					break;
				case 6:
					CreateObject<Enemy>(Vector2D(40.0f, 400.0f), enemy_rand, 0.0f);
					break;
				}
			}
			enemy_count++;
			create_rand = GetRand(1);
		}
		count_rand = (GetRand(1) + 1) * 100;
		enemy_rand = GetRand(3)+3;
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

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Bomb>(objects[0]->GetLocation(), 2, 0.0f);

	}
	if (InputControl::GetKey(KEY_INPUT_X))
	{
		CreateObject<Bomb>(objects[0]->GetLocation(), 2, 0.0f);
	}
	for (int i = 0; i <= objects.size()-1; i++)
	{
		if (objects[i]->GetShotFlag() == TRUE)
		{
			Vector2D P = objects[0]->GetLocation();
			Vector2D E = objects[i]->GetLocation();
			float a = ((P.x - E.x) * (P.x - E.x) + (P.y - E.y) * (P.y - E.y));
			CreateObject<EnemyBullet>(objects[i]->GetLocation(), 7, ((P - E) / a));
		}
	}
	if (score < 0)
	{
		score = 0;
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
	scores->Update(score);
}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawExtendGraph(0, 0, 640, 480, Background, FALSE);
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	scores->Draw();
	DrawFormatString(300, 450, 0xffffff, "%d", score);
	DrawFormatString(10, 10, 0x000000, "%d", enemy_count);
}

//終了時処理
void Scene::Finalize()
{

	scores->Finalize();

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
}

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D diff = a->GetLocation() - b->GetLocation();

	Vector2D box_size = (a->GetScale() + b->GetScale()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		if ((a->GetType() != b->GetType()) && (a->GetType() == 2 || b->GetType() == 2))
		{
			score += a->GetSca();
			score += b->GetSca();
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
}