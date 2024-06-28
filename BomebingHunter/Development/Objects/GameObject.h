#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/ResourceManager.h"
#include <vector>

#define D_PIVOT_CENTER		//座標の原点を画像の中心にする

enum ObjectType
{
	ePlayer,
	eBome,
	eBoxEnemy,
	eFlyEnemy,
	eHarpy,
	eGoldEnemy,
	eEnemyBullet,
};

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;			//位置情報
	Vector2D box_size;			//大きさ
	Vector2D direction;			//移動方向
	double radian;				//向き
	int image;					//描画する画像
	int sound;					//再生する音源
	ObjectType type;			//プレイヤーか敵かを判断する
	bool Delete;				//削除フラグ
	bool shot_flag;				//敵のショットフラグ
	int score;					//加点するスコア
	std::vector<int> animation;			//アニメーション画像

	ResourceManager* rm = ResourceManager::GetInstance();

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();			//初期化処理
	virtual void Update();				//更新処理
	virtual void Draw() const;			//描画処理
	virtual void Finalize();			//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);
	//当たり判定の大きさ取得処理
	Vector2D GetScale() const;
	//種類取得処理
	int GetType() const;
	//削除フラグ取得処理
	bool GetDelete() const;
	//移動方向変更処理
	void SetDirection(const Vector2D& direction);
	//移動方向取得処理
	Vector2D GetDirection() const;
	//種類変更処理
	void SetType(const ObjectType type);
	//ショットフラグ取得処理
	bool GetShotFlag() const;
	//スコア取得処理
	int GetScore() const;
};