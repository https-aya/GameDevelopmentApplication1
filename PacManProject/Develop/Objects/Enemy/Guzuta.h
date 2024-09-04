#pragma once

#include "EnemyTypeBase.h"

class Guzuta : public EnemyTypeBase
{
private:

public:
	Guzuta(class EnemyBase* e);
	~Guzuta();

	virtual void Initialize() override;

private:
	virtual void IdolMove(float delta_second) override;
	virtual void PatorolMove(float delta_second);
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

