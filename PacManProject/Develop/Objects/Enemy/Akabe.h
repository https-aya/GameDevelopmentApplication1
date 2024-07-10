#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe();
	~Akabe();

	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void Finalize() override;

private:
	void IdleMove();
	void AttackMove();
	void PatrolMove();
	void IzikeMove();
	void EscapeMove();
	void AnimationControl(float) override;
};

