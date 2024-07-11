#pragma once

#include "EnemyBase.h"

class Enemy : public EnemyBase
{
private:

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Draw(const Vector2D& screen_offset) const;
	void Finalize();

private:
	void IdleMove();
	void AttackMove();
	void PatrolMove();
	void IzikeMove();
	void EscapeMove();
	void AnimationControl(float);
};

