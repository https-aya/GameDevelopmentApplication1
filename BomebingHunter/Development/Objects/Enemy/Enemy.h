#pragma once

#include "../GameObject.h"
#include "../../Scene/FlyText.h"

class Enemy : public GameObject
{
private:
	int animation_count;				//アニメーション時間
	int max_animation;					//アニメーションの最大数
	int anime_time;						//どのアニメーションか
	int shot_count;						//敵弾を打つ間隔
	int shot_rand;						//敵弾の間隔をランダムにする
	int alpha;							//画像の透明度
	bool blend_flag;					//透明化フラグ
	Vector2D anim_location;

	FlyText* fly_text = new FlyText;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;			//初期化処理
	virtual void Update() override;				//更新処理
	virtual void Draw() const override;			//描画処理
	virtual void Finalize() override;			//終了時処理


	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimeControl();
};

