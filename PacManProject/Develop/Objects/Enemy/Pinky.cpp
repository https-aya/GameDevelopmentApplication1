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
	int lx;
	int ly;
	move_count += delta_second;
	if (move_count >= (1.0f / 2.0f))
	{
		if (now_direction == eEnemyDirectionState::UP || now_direction == eEnemyDirectionState::LEFT)
		{
			lx = (enemy->GetLocation().x - (D_OBJECT_SIZE / 2.0f + 2)) / D_OBJECT_SIZE + 1;
			ly = (enemy->GetLocation().y - (D_OBJECT_SIZE / 2.0f + 2)) / D_OBJECT_SIZE + 1;
		}
		else
		{
			lx = (enemy->GetLocation().x - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE;
			ly = (enemy->GetLocation().y - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE;
		}
		if (panel == ePanelID::BRANCH && x == lx && y == ly)
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
				else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::UP)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
				else
				{
					if (ret[eAdjacentDirection::LEFT] != ePanelID::WALL && now_direction != eEnemyDirectionState::RIGHT)
					{
						now_direction = eEnemyDirectionState::LEFT;
					}
					else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL && now_direction != eEnemyDirectionState::LEFT)
					{
						now_direction = eEnemyDirectionState::RIGHT;
					}
					else if (ret[eAdjacentDirection::UP] != ePanelID::WALL && now_direction != eEnemyDirectionState::DOWN)
					{
						now_direction = eEnemyDirectionState::UP;
					}
					else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL && now_direction != eEnemyDirectionState::UP)
					{
						now_direction = eEnemyDirectionState::DOWN;
					}
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
				else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else
				{
					if (ret[eAdjacentDirection::UP] != ePanelID::WALL && now_direction != eEnemyDirectionState::DOWN)
					{
						now_direction = eEnemyDirectionState::UP;
					}
					else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL && now_direction != eEnemyDirectionState::UP)
					{
						now_direction = eEnemyDirectionState::DOWN;
					}
					else if (ret[eAdjacentDirection::LEFT] != ePanelID::WALL && now_direction != eEnemyDirectionState::RIGHT)
					{
						now_direction = eEnemyDirectionState::LEFT;
					}
					else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL && now_direction != eEnemyDirectionState::LEFT)
					{
						now_direction = eEnemyDirectionState::RIGHT;
					}
				}
			}
			move_count = 0.0f;
		}
	}
}

void Pinky::AttackMove(float delta_second, Player* playerdate)
{
	__super::AttackMove(delta_second, playerdate);
	StageData::ConvertToIndex(player->GetLocation(), target_panel_y, target_panel_x);
	switch (player->GetNowDirection())
	{
	case eDirectionState::pUP:
		target_panel_y += 2;
		break;
	case eDirectionState::pDOWN:
		target_panel_y -= 2;
		break;
	case eDirectionState::pLEFT:
		target_panel_x += 2;
		break;
	case eDirectionState::pRIGHT:
		target_panel_x -= 2;
	}
	int lx;
	int ly;
	move_count += delta_second;
	if (move_count >= (1.0f / 2.0f))
	{
		if (now_direction == eEnemyDirectionState::UP || now_direction == eEnemyDirectionState::LEFT)
		{
			lx = (enemy->GetLocation().x - (D_OBJECT_SIZE / 2.0f + 2)) / D_OBJECT_SIZE + 1;
			ly = (enemy->GetLocation().y - (D_OBJECT_SIZE / 2.0f + 2)) / D_OBJECT_SIZE + 1;
		}
		else
		{
			lx = (enemy->GetLocation().x - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE;
			ly = (enemy->GetLocation().y - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE;
		}
		if (panel == ePanelID::BRANCH && x == lx && y == ly)
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
				else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else if (target_panel_y < y && ret[eAdjacentDirection::UP] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::DOWN)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::UP)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
				else
				{
					if (ret[eAdjacentDirection::LEFT] != ePanelID::WALL&& now_direction != eEnemyDirectionState::RIGHT)
					{
						now_direction = eEnemyDirectionState::LEFT;
					}
					else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL&& now_direction != eEnemyDirectionState::LEFT)
					{
						now_direction = eEnemyDirectionState::RIGHT;
					}
					else if (ret[eAdjacentDirection::UP] != ePanelID::WALL&& now_direction != eEnemyDirectionState::DOWN)
					{
						now_direction = eEnemyDirectionState::UP;
					}
					else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL&& now_direction != eEnemyDirectionState::UP)
					{
						now_direction = eEnemyDirectionState::DOWN;
					}
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
				else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL
					&& now_direction != eEnemyDirectionState::LEFT)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else
				{
					if (ret[eAdjacentDirection::UP] != ePanelID::WALL && now_direction != eEnemyDirectionState::DOWN)
					{
						now_direction = eEnemyDirectionState::UP;
					}
					else  if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL && now_direction != eEnemyDirectionState::UP)
					{
						now_direction = eEnemyDirectionState::DOWN;
					}
					else if (ret[eAdjacentDirection::LEFT] != ePanelID::WALL && now_direction != eEnemyDirectionState::RIGHT)
					{
						now_direction = eEnemyDirectionState::LEFT;
					}
					else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL && now_direction != eEnemyDirectionState::LEFT)
					{
						now_direction = eEnemyDirectionState::RIGHT;
					}

				}
			}
			move_count = 0.0f;
		}
	}
}