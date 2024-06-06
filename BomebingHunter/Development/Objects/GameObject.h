#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//座標の原点を画像の中心にする

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
	int type;					//プレイヤーか敵かを判断する
	bool Delete;				//削除フラグ
	bool shot_flag;				//敵のショットフラグ
	int sca;					//獲得できるスコア

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
	//種類変更処理
	void SetType(const int type);
	//ショットフラグ取得処理
	bool GetShotFlag() const;
	//スコア取得処理
	int GetSca() const;
};