#pragma once

#include "EnemyBase.h"

class Aosuke : public EnemyBase
{
private:

public:
	Aosuke();
	~Aosuke();

	virtual void Initialize() override;


private:
	virtual void AttackMove(float delta_second) override;
};

