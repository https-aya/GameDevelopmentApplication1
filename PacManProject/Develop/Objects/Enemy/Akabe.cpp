#include "Akabe.h"
#include "../../Utility/ResourceManager.h"
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
	now_direction = eEnemyDirectionState::LEFT;
	fast = true;
}

void Akabe::PatorolMove(float delta_second)
{
	__super::PatorolMove(delta_second);
	move_count += delta_second;
	if (move_count >= (1.0f / 2.0f))
	{
		if (panel == ePanelID::BRANCH)
		{
			int x, y;
			StageData::ConvertToIndex(enemy->GetLocation(), y, x);
			if (fast == true)
			{
				target_panel_x = 7;
				target_panel_y = 6;
			}
			else
			{
				target_panel_x = 25;
				target_panel_y = 1;
			}
			if (x == target_panel_x - 1 && y == target_panel_y - 1)
			{
				fast = false;
			}
			int px = target_panel_x - x;
			int py = target_panel_y - y;
			if (px < 0)
			{
				px *= -1;
			}
			if (py < 0)
			{
				py *= -1;
			}
			if (px > py)
			{
				if (target_panel_x > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else if (target_panel_x < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::RIGHT)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
			}
			else
			{
				if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}				
				else if (target_panel_x > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else if (target_panel_x < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::RIGHT)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}		
			}
			move_count = 0;
		}
	}
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