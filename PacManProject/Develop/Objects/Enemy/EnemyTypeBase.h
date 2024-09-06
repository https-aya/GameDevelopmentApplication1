#pragma once
#include "Enum/EnemyType.h"
#include "Enum/EnemyState.h"
#include "../../Utility/Vector2D.h"
#include "../Player/Player.h"
#include "EnemyBase.h"

class EnemyTypeBase
{
protected:
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

protected:
	std::vector<int> animation;			//アニメーション
	std::vector<int> eyeanimation;		//目のアニメーション

	eEnemyType type;					//エネミーの種類
	eEnemyState enemy_state;			//エネミーの状態
	eEnemyDirectionState now_direction; //向いてる方向
	Vector2D velocity;					//移動方向
	class EnemyBase* enemy;				//エネミーの情報
	class Player* player;				//プレイヤー情報
	eEnemyDeltaState enemy_delta;		//エネミーの生体情報

	std::map<eAdjacentDirection, ePanelID> ret; //上下左右のパネル情報
	ePanelID panel;								//現在地パネル情報
	float move_count;							//移動のカウント
	int target_panel_x;							//目標パネルｘ
	int target_panel_y;							//目標パネルｙ
	int x;										//現在パネルｘ
	int	y;										//現在パネルｙ

private:

	int flash_count;							//エネミーがいじけから戻るときの点滅
	float izike_time;							//いじけ中のカウント
	float animation_time;						//
	int animation_count;
	bool fast;
	int eye_image;
	int image;

public:
	EnemyTypeBase(class EnemyBase* e);


	virtual ~EnemyTypeBase() = default;

public:
	//初期化処理関数
	virtual void Initialize();

	//更新処理
	void Update(float delta_second ,class EnemyBase* e);

	//描画処理
	void Draw(const Vector2D& screen_offset) const;

	//終了処理関数
	void Finalize();



protected:
	virtual void AnimationControl(float delta_second);
	void Movement(float delta_second);
	virtual void IdolMove(float delta_second);
	virtual void PatorolMove(float delta_second);
	void IzikeMove(float delta_second);
	void EscapeMove(float delta_second);
	void EscMonsterRoom(float delta_second);

protected:
	virtual void AttackMove(float delta_second, Player* playerdate);
};

 