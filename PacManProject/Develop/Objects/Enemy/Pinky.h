#pragma once

#include "EnemyBase.h"

class Pinky : public EnemyBase
{
private:

public:
	Pinky(class EnemyBase* e);
	~Pinky();

	virtual void Initialize() override;

private:
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

