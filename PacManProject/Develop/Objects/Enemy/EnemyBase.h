#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"





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
	class EnemyTypeBase* enemy_type;
	eEnemyState enemy_state;
	eEnemyState hold_state;
	eEnemyDirectionState now_direction;
	class Player* player;
	int eye_image;
	int x;
	int y;
	int hx;
	int hy;
	char j;

private:
	float world_time;
	int flash_count;
	float izike_time;
	float animation_time;
	int animation_count;
	int animation_num;
	float move_count;
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
	void SetEnemytype(int);
	void SetPlayer(Player* object);
	eEnemyType GetEnemytype() const;
};