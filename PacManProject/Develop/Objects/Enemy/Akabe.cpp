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
	type = eEnemyType::AKABE;
	now_direction = eEnemyDirectionState::LEFT;
	__super::Initialize();
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
				else if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
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
				else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL
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