#pragma once

#include "EnemyBase.h"

class Pinky : public EnemyBase
{
private:

public:
	Pinky();
	~Pinky();

	virtual void Initialize() override;


private:
	virtual void AttackMove(float delta_second) override;
};

