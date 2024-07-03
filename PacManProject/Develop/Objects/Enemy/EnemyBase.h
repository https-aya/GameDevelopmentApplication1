#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

enum eEnemyType {
	Akabe,
	Pinky,
	Aosuke,
	Guzuta,
};

class EnemyBase : public GameObject
{
protected:
	std::vector<int> Animation;
	std::vector<int> MoveAnimation;
public:
	EnemyBase();
	virtual ~EnemyBase();
};