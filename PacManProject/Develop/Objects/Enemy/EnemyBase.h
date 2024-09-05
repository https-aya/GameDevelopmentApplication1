#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"
#include "Enum/EnemyState.h"
#include "Enum/EnemyType.h"





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
	class EnemyTypeBase* enemy_type;
	eEnemyState enemy_state;
	eEnemyState hold_state;
	Vector2D velocity;
	class Player* player;

private:
	float world_time;
	int flash_count;
	float izike_time;
	int life;

public:	

	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	eEnemyState GetEnemyState();
	void ChangeEnemyState(eEnemyState state);
	void SetEnemytype();
	void SetPlayer(Player* object);
	Player* GetPlayer();
	void SetVelocity(Vector2D velocity);
	void SetMobility(eMobilityType mobility);
	void SetLife(int num);
	float GetWorldTime();
	void ClearWorldTime();
};