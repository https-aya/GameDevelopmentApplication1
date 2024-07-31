#pragma once

#include "EnemyBase.h"

class Aosuke : public EnemyBase
{
private:

public:
	Aosuke(class EnemyBase* e);
	~Aosuke();

	virtual void Initialize() override;
	void Draw(const Vector2D& screen_offset, Vector2D loc) const;

private:
	virtual void AttackMove(float delta_second) override;
};

