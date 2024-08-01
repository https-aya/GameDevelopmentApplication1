#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe(class EnemyBase* e);
	~Akabe();

	virtual void Initialize() override;

private:
	virtual void AttackMove(float delta_second) override;
	virtual int GetImage() const override;
};

