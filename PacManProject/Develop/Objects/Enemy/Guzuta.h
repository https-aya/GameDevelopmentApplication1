#pragma once

#include "EnemyBase.h"

class Guzuta : public EnemyBase
{
private:

public:
	Guzuta();
	~Guzuta();

	virtual void Initialize() override;


private:
	virtual void AttackMove(float delta_second) override;
};

