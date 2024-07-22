#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe();
	~Akabe();

	virtual void Initialize() override;


private:
	virtual void AttackMove(float delta_second) override;
};

