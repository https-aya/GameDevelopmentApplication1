#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe();
	~Akabe();

	void Initialize();
	eEnemyType Update();
	void Draw() const;
	void Finalize();

private:
	void IdleMove();
	void AttackMove();
	void PatrolMove();
	void IzikeMove();
	void EscapeMove();
	void AnimationControl(float);
};

