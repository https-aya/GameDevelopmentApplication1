#pragma once

#include "EnemyTypeBase.h"

class Akabe : public EnemyTypeBase
{
private:

public:
	Akabe(class EnemyBase* e);
	~Akabe();

	virtual void Initialize() override;

private:
	virtual void PatorolMove(float delta_second);
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

