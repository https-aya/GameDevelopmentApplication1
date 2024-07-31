#pragma once

#include "EnemyBase.h"

class Pinky : public EnemyBase
{
private:

public:
	Pinky(class EnemyBase* e);
	~Pinky();

	virtual void Initialize() override;
	void Draw(const Vector2D& screen_offset, Vector2D loc) const;

private:
	virtual void AttackMove(float delta_second) override;
};

