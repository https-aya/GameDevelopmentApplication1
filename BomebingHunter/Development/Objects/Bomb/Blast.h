#pragma once

#include "../GameObject.h"

class Blast : public GameObject
{
private:
	int animation[3];
	int anime_count;
	int anime_num;
	Vector2D location;

public:
	Blast();
	~Blast();

	virtual void Initialize() override;
	virtual void Update()	override;
	virtual void Draw() const override;
	virtual void Finalize() override;

private:
	void AnimeControl();
};

