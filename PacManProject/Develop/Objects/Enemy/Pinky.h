#pragma once

#include "EnemyTypeBase.h"

class Pinky : public EnemyTypeBase
{
private:

public:
	Pinky(class EnemyBase* e);
	~Pinky();

	virtual void Initialize() override;

private:
	virtual void IdolMove(float delta_second) override;
	virtual void PatorolMove(float delta_second);
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

