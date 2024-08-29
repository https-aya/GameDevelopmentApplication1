#pragma once

#include "EnemyTypeBase.h"

class Akabe : public EnemyTypeBase
{
private:

public:
	Akabe(class EnemyBase* e);
	~Akabe();

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

private:
	virtual void AttackMove(float delta_second, Player* playerdate) override;
};

