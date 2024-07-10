#pragma once

#include "../GameObject.h"


enum eEnemyState 
{
	eIDLE,
	eATTACK,
	ePATOROL,
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
	eEnemyType enemy_type;
	eEnemyState enemy_state;
	eEnemyDirectionState now_direction;
	eEnemyDirectionState next_direction;
	int animation_count;
	float animation_time;


public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	virtual void AnimationControl(float delta_second);
};