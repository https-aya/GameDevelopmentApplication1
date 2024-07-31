#pragma once

#include "EnemyBase.h"

class Guzuta : public EnemyBase
{
private:

public:
	Guzuta(class EnemyBase* e);
	~Guzuta();

	virtual void Initialize() override;
	void Draw(const Vector2D& screen_offset, Vector2D loc) const;

private:
	virtual void AttackMove(float delta_second) override;
};

