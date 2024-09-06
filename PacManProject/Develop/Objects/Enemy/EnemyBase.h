#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"
#include "Enum/EnemyState.h"
#include "Enum/EnemyType.h"
#include "Enum/EnemyDeltaState.h"





class EnemyBase : public GameObject
{
private:
enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

private:
	class EnemyTypeBase* enemy_type;	//エネミーの種類
	eEnemyState enemy_state;			//エネミーの現在の状態
	eEnemyState hold_state;				//エネミーの状態を変更する際の変数
	Vector2D velocity;					//移動方向と速度
	class Player* player;				//プレイヤー情報t
	eEnemyDeltaState enemy_delta;		//エネミーの生体情報

private:
	float world_time;				//エネミーの状態を切り替えるためのカウント
	int flash_count;				//エネミーがいじけから戻るときの点滅
	float izike_time;				//いじけ中のカウント

public:	

	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;		
	eEnemyState GetEnemyState();						//エネミーの状態の取得
	void ChangeEnemyState(eEnemyState state);			//エネミーの状態の変更
	void SetEnemytype();								//エネミーの種類を設定
	void SetPlayer(Player* object);						//プレイヤー情報の設定
	Player* GetPlayer();								//プレイヤー情報の取得
	void SetVelocity(Vector2D velocity);				//移動情報の取得
	void SetMobility(eMobilityType mobility);			//可動性の変更
	void SetEnemyDeltaState(eEnemyDeltaState delta);								//ライフ情報の取得
	float GetWorldTime();								//カウントの取得
	void ClearWorldTime();								//カウントの初期化
};