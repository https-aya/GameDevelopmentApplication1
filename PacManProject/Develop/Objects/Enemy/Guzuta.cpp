#include "Guzuta.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Guzuta::Guzuta(class EnemyBase* e)
	:EnemyTypeBase(e)
{

}

Guzuta::~Guzuta()
{

}

void Guzuta::Initialize()
{
	__super::Initialize();
	animation_num = 6;
	image = animation[animation_num];
	eye_image = eyeanimation[0];
	now_direction = eEnemyDirectionState::DOWN;
}

void Guzuta::IdolMove(float delta_second)
{
	__super::IdolMove(delta_second);
	if (player->GetFoodCount() >= 55)
	{
		EscMonsterRoom(delta_second);
	}
}

void Guzuta::AttackMove(float delta_second, Player* playerdate)
{

}