#pragma once

#include "EnemyTypeBase.h"

class Aosuke : public EnemyTypeBase
{
private:

public:
	Aosuke(class EnemyBase* e);
	~Aosuke();

	virtual void Initialize() override;

private:
	virtual void IdolMove(float delta_second) override;
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

