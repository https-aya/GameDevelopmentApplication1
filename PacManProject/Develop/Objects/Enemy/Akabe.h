#pragma once

#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:

public:
	Akabe(class EnemyBase* e);
	~Akabe();

	virtual void Initialize() override;
	void Draw(const Vector2D& screen_offset, Vector2D loc) const;


private:
	virtual void AttackMove(float delta_second) override;
};

