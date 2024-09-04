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
	type = eEnemyType::GUZUTA;
	now_direction = eEnemyDirectionState::DOWN;
	__super::Initialize();
}

void Guzuta::IdolMove(float delta_second)
{
	__super::IdolMove(delta_second);
	if (player->GetFoodCount() >= 15)
	{
		EscMonsterRoom(delta_second);
	}
}

void Guzuta::PatorolMove(float delta_second)
{
	__super::PatorolMove(delta_second);
	move_count += delta_second;
	if (move_count >= (1.0f / 2.0f))
	{
		if (panel == ePanelID::BRANCH)
		{
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
				else if (target_panel_x > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}	
				else if (target_panel_y > y && ret[eAdjacentDirection::DOWN] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::UP)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
				else if (ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
			}
			else
			{
				if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else  if (target_panel_y > y && ret[eAdjacentDirection::DOWN] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::UP)
				{
					now_direction = eEnemyDirectionState::DOWN;
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
			}
			move_count = 0.0f;
		}
	}
}

void Guzuta::AttackMove(float delta_second, Player* playerdate)
{

}