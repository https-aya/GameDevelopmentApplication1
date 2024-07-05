#pragma once

#include "../GameObject.h"


enum eEnemyType {
	Akabe,
	Pinky,
	Aosuke,
	Guzuta,
};

enum eEnemyState 
{
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
	std::vector<int> Animation;
	std::vector<int> MoveAnimation;
	eEnemyType enemy_type;
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
	virtual void Movement(float delta_second);
	virtual void AnimationControl(float delta_second);
};