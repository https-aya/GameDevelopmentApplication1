#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe();
	~Akabe();

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
	void AnimationControl(float second);
};

