#pragma once

#include "../GameObject.h"

class EnemyBullet : public GameObject
{
private:
	bool anime_flag;		//アニメーションするかどうか
	int anime_count;		//アニメーション時間
	int anime_num;			//アニメーション番号

public:
	EnemyBullet();
	~EnemyBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション管理
	void AnimeControl();

};

