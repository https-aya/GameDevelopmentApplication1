#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"
#include "Score.h"
#include "TimeUp.h"

#define MAX_ENEMY (6)	//画面内で生成する敵の最大数

class Scene
{
private:
	std::vector<GameObject*> objects;
private:
	std::vector<int> sound;				//音源
	int Background;			//背景画像
	int count_time;			//生成間隔のカウント
	int count_rand;			//ランダムで生成間隔を決める
	int create_rand;		//生成位置をランダムで決める
	int enemy_rand;			//生成する敵をランダムで決める
	int enemy_count;		//敵の生成数

	//ローカル変数定義
	Score* scores = new Score;
	TimeUp* time_up = new TimeUp;

public:
	//コンストラクタ
	Scene();
	//デストラクタ
	~Scene();

	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw() const;
	//終了時処理
	void Finalize();

private:
	//当たり判定チェック
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location,ObjectType enemy_type,const Vector2D& direction)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//種類の設定
		new_object->SetType(enemy_type);

		//位置情報の設定
		new_object->SetLocation(location);

		//移動方向の設定
		new_object->SetDirection(direction);

		//初期化処理
		new_object->Initialize();

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};

