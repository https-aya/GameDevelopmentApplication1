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
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

