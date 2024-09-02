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
	fast = true;
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
				if (x == target_panel_x - 1 && y == target_panel_y - 1)
				{
					fast = false;
				}
			}
			if(fast == false)
			{
				target_panel_x = 4;
				target_panel_y = 1;
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
			if (px >= py)
			{
				if (target_panel_x < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::RIGHT)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else if (target_panel_x > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
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
				else if (target_panel_x < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::RIGHT)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (target_panel_x > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
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

void Pinky::AttackMove(float delta_second, Player* playerdate)
{

}