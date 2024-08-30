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
	__super::Initialize();
	animation_num = 4;
	image = animation[animation_num];
	eye_image = eyeanimation[0];
	now_direction = eEnemyDirectionState::DOWN;
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