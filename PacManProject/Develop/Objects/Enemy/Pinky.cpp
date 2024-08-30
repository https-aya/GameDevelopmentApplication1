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
	__super::Initialize();
	animation_num = 2;
	image = animation[animation_num];
	eye_image = eyeanimation[0];
	now_direction = eEnemyDirectionState::UP;
}

void Pinky::IdolMove(float delta_second)
{
	__super::IdolMove(delta_second);
	if (player->GetFoodCount() >= 5)
	{
		EscMonsterRoom(delta_second);
	}
}

void Pinky::AttackMove(float delta_second, Player* playerdate)
{

}