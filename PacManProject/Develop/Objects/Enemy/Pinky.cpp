#include "Pinky.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Pinky::Pinky(class EnemyBase* e)
	:EnemyTypeBase(e)
{

}

Pinky::~Pinky()
{

}

void Pinky::Initialize()
{
	type = eEnemyType::PINKY;
	now_direction = eEnemyDirectionState::UP;
	__super::Initialize();
}

void Pinky::IdolMove(float delta_second)
{
	__super::IdolMove(delta_second);
	if (player->GetFoodCount() >= 5)
	{
		EscMonsterRoom(delta_second);
	}
}

void Pinky::PatorolMove(float delta_second)
{
	__super::PatorolMove(delta_second);
	
}

void Pinky::AttackMove(float delta_second, Player* playerdate)
{

}