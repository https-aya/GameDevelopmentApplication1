#include "Aosuke.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Aosuke::Aosuke(class EnemyBase* e)
	:EnemyTypeBase(e)
{

}

Aosuke::~Aosuke()
{

}

void Aosuke::Initialize()
{
	type = eEnemyType::AOSUKE;
	now_direction = eEnemyDirectionState::DOWN;
	__super::Initialize();
}

void Aosuke::IdolMove(float delta_second)
{
	__super::IdolMove(delta_second);
	if (player->GetFoodCount() >= 35)
	{
		EscMonsterRoom(delta_second);
	}
}

void Aosuke::AttackMove(float delta_second, Player* playerdate)
{

}