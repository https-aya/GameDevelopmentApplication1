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
	std::vector<int> animation;
	std::vector<int> eyeanimation;

	eEnemyType type;
	eEnemyState enemy_state;
	eEnemyState hold_state;
	eEnemyDirectionState now_direction;
	Vector2D velocity;
	class EnemyBase* enemy;
	class Player* player;

	std::map<eAdjacentDirection, ePanelID> ret;
	ePanelID panel;
	float move_count;
	int target_panel_x;
	int target_panel_y;

private:

	int x;
	int	y;
	float world_time;
	int flash_count;
	float izike_time;
	float animation_time;
	int animation_count;
	int life;
	bool fast;
	int eye_image;
	int image;

public:
	EnemyTypeBase(class EnemyBase* e);


	virtual ~EnemyTypeBase() = default;

public:
	//‰Šú‰»ˆ—ŠÖ”
	virtual void Initialize();

	//XVˆ—
	virtual void Update(float delta_second ,class EnemyBase* e);

	//•`‰æˆ—
	virtual void Draw(const Vector2D& screen_offset) const;

	//I—¹ˆ—ŠÖ”
	virtual void Finalize();

protected:
	virtual void AnimationControl(float delta_second);
	virtual void Movement(float delta_second);
	virtual void IdolMove(float delta_second);
	virtual void PatorolMove(float delta_second);
	virtual void IzikeMove(float delta_second);
	virtual void EscapeMove(float delta_second);
	virtual void EscMonsterRoom(float delta_second);

protected:
	virtual void AttackMove(float delta_second, Player* playerdate);
};

 