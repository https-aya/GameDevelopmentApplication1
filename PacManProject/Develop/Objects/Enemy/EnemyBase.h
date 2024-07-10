#pragma once

#include "../GameObject.h"


enum eEnemyState 
{
	IDLE,
	ATTACK,
	PATOROL,
	IZIKE,
	ESCAPE,
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
	eEnemyState enemy_state;
	eEnemyDirectionState now_direction;
	eEnemyDirectionState next_direction;
	int animation_count;
	float animation_time;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

private:
	virtual void AnimationControl(float delta_second);
};