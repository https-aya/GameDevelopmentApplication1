#include "Scene.h"
#include "DxLib.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/boxEnemy.h"
#include "../Objects/Enemy/WingEnemy.h"

//コンストラクタ
Scene::Scene() : objects(), Background(NULL), counttime(),countrand(),createrand()
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
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
	CreateObject<boxEnemy>(Vector2D(600.0f, 400.0f));
	CreateObject<WingEnemy>(Vector2D(600.0f, 300.0f));
	counttime = 1;
	countrand = 1000;
	createrand = 0;
	Background = LoadGraph("Resource/Images/BackGround.png");
}

//更新処理
void Scene::Update()
{
	counttime++;
	//シーンに存在するオブジェクトの更新処理
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
}

//終了時処理
void Scene::Finalize()
{
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