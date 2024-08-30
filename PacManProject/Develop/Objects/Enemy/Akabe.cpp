#include "Akabe.h"
#include "../../Utility/ResourceManager.h"
#include "EnemyBase.h"
#include "DxLib.h"

Akabe::Akabe(class EnemyBase* e)
	:EnemyTypeBase(e)
{

}

Akabe::~Akabe()
{

}

void Akabe::Initialize()
{	
	__super::Initialize();
	animation_num = 0;
	image = animation[animation_num];
	eye_image = eyeanimation[0];
	now_direction = eEnemyDirectionState::RIGHT;
}

void Akabe::AttackMove(float delta_second, Player* playerdate)
{
	/*Vector2D target = player->GetLocation();

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE },
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	if (target.y < location.y)
	{
		if (ret[eAdjacentDirection::UP] != WALL)
		{
			now_direction = eEnemyDirectionState::UP;
		}
		else
		{
			if (target.x < location.x)
			{
				now_direction = eEnemyDirectionState::LEFT;
			}
			else
			{
				now_direction = eEnemyDirectionState::RIGHT;
			}
		}
	}
	else
	{
		if (ret[eAdjacentDirection::DOWN] != WALL)
		{
			now_direction = eEnemyDirectionState::DOWN;
		}
		else
		{
			if (target.x < location.x)
			{
				now_direction = eEnemyDirectionState::LEFT;
			}
			else
			{
				now_direction = eEnemyDirectionState::RIGHT;
			}
		}
	}*/
}