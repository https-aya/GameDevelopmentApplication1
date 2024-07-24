#pragma once

#include "../GameObject.h"

enum eEnemyState 
{
	eIDLE,
	eATTACK,
	ePATROL,
	eIZIKE,
	eESCAPE,
};

enum eEnemyType
{
	AKABE,
	AOSUKE,
	PINKY,
	GUZUTA,
};


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

protected:
	std::vector<int> animation;
	std::vector<int> eyeanimation;
	Vector2D velocity;
	eEnemyType enemy_type;
	eEnemyState enemy_state;
	eEnemyDirectionState now_direction;
	class Player* player_date;


private:
	float world_time;
	int flash_count;
	float izike_time;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;


private:
	virtual void AnimationControl(float delta_second);
	virtual void Movement(float delta_second);
	virtual void IdolMovement(float delta_second);
	virtual void PatorolMove(float delta_second);
	virtual void IzikeMove(float delta_second);
	virtual void EscapeMove(float delta_second);

protected:
	virtual void AttackMove(float delta_second);

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
	eEnemyState GetEnemyState();
	void ChangeEnemyState(eEnemyState state);
	void SetEnemytype(int);
	void SetPlayer(GameObjectBase* object);
};