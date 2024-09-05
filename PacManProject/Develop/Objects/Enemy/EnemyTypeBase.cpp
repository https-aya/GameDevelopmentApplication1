#include "EnemyTypeBase.h"
#include "../../Utility/ResourceManager.h" 
#include "DxLib.h"

EnemyTypeBase::EnemyTypeBase(class EnemyBase* e) : enemy(e)
, animation()
, eyeanimation()
, image()
, fast()
, target_panel_x(0)
, target_panel_y(0)
{

}

void EnemyTypeBase::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
	enemy_state = enemy->GetEnemyState();
	eye_image = eyeanimation[0];
	image = animation[type * 2];
	fast = true;
}

void EnemyTypeBase::Update(float delta_second , class EnemyBase* e)
{
	enemy = e;
	player = enemy->GetPlayer();
	enemy_state = enemy->GetEnemyState();
	Movement(delta_second);
	AnimationControl(delta_second);
	if (enemy_state == eEnemyState::eIZIKE)
	{
		life = 1;
	}
	if (life == 1 || life == 2)
	{
		izike_time += delta_second;
		if (izike_time >= 7.0f && flash_count == 0)
		{
			flash_count = 1;
		}
		if (izike_time >= 8.0f)
		{
			izike_time = 0.0f;
			flash_count = 0;
			enemy->SetLife(0);
		}
	}

}

void EnemyTypeBase::Draw(const Vector2D& screen_offset) const
{
	if (enemy_state != eEnemyState::eESCAPE)
	{
		Vector2D graph_location = enemy->GetLocation() + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
	}
	if (enemy_state != eEnemyState::eIZIKE)
	{
		Vector2D graph_location = enemy->GetLocation() + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
	int color;
	switch (type)
	{
	case AKABE:
		color = 0xff0000;
		break;
	case PINKY:
		color = 0xff66cc;
		break;
	case AOSUKE:
		color = 0x0000ff;
		break;
	case GUZUTA:
		color = 0xffaaaa;
		break;
	default:
		break;
	}
	DrawFormatString(type * 100, 50, color, "%d,%d,%f", x, y , enemy->GetLocation().y);
}

void EnemyTypeBase::Finalize()
{
	animation.clear();
	eyeanimation.clear();
}

void EnemyTypeBase::AnimationControl(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_count += 1;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		animation_time = 0.0f;
		if (enemy_state == eEnemyState::eIZIKE)
		{
			switch (flash_count)
			{
			case 1:
				flash_count += 1;
			case 0:
				image = animation[16 + animation_count];
				break;
			case 2:
				image = animation[18 + animation_count];
				flash_count += -1;
				break;
			}
		}
		else
		{
			image = animation[type * 2 + animation_count];
		}
	}
	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		eye_image = eyeanimation[0];
		break;
	case eEnemyDirectionState::RIGHT:
		eye_image = eyeanimation[1];
		break;
	case eEnemyDirectionState::DOWN:
		eye_image = eyeanimation[2];
		break;
	case eEnemyDirectionState::LEFT:
		eye_image = eyeanimation[3];
		break;
	}
}

void EnemyTypeBase::Movement(float delta_second)
{
	switch (enemy_state)
	{
	case eIDLE:
		IdolMove(delta_second);
		break;
	case ePATROL:
		PatorolMove(delta_second);
		break;
	case eATTACK:
		AttackMove(delta_second, player);
		break;
	case eESCAPE:
		EscapeMove(delta_second);
		break;
	case eIZIKE:
		IzikeMove(delta_second);
		break;
	}
	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		velocity.y = -2.0f;
		velocity.x = 0.0f;
		break;
	case eEnemyDirectionState::DOWN:
		velocity.y = 2.0f;
		velocity.x = 0.0f;
		break;
	case eEnemyDirectionState::LEFT:
		velocity.x = -2.0f;
		velocity.y = 0.0f;
		break;
	case eEnemyDirectionState::RIGHT:
		velocity.x = 2.0f;
		velocity.y = 0.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}
	if (enemy_state == eEnemyState::eESCAPE)
	{
		velocity *= 2.0f;
	}
	// ˆÚ“®—Ê * ‘¬‚³ * ŽžŠÔ ‚ÅˆÚ“®æ‚ðŒˆ’è‚·‚é
	enemy->SetVelocity(Vector2D(velocity));
}

void EnemyTypeBase::IdolMove(float delta_second)
{
	ret = StageData::GetAdjacentPanelData(enemy->GetLocation());
	move_count += delta_second;
	if (move_count >= (1.0f / 4.0f))
	{
		if (ret[eAdjacentDirection::UP] == WALL)
		{
			now_direction = eEnemyDirectionState::DOWN;
		}
		else if (ret[eAdjacentDirection::DOWN] == WALL)
		{
			now_direction = eEnemyDirectionState::UP;
		}
		move_count = 0;
	}
}

void EnemyTypeBase::PatorolMove(float delta_second)
{
	ret = StageData::GetAdjacentPanelData(enemy->GetLocation());
	panel = StageData::GetPanelData(enemy->GetLocation());
	StageData::ConvertToIndex(enemy->GetLocation(), y, x);
	if (fast == true)
	{
		target_panel_x = 7;
		target_panel_y = 15;
		if (x == target_panel_x - 1 && y == target_panel_y - 1)
		{
			fast = false;
		}
	}
	if (fast == false)
	{
		switch (type)
		{
		case AKABE:
			target_panel_x = 22;
			target_panel_y = 3;
			break;
		case PINKY:
			target_panel_x = 5;
			target_panel_y = 3;
			break;
		case AOSUKE:
			target_panel_x = 23;
			target_panel_y = 28;
			break;
		case GUZUTA:
			target_panel_x = 3;
			target_panel_y = 27;
			break;
		default:
			break;
		}
	}
}

void EnemyTypeBase::IzikeMove(float delta_second)
{

	enemy->SetMobility(eMobilityType::Movable);
	ret = StageData::GetAdjacentPanelData(enemy->GetLocation());
	panel = StageData::GetPanelData(enemy->GetLocation());
	StageData::ConvertToIndex(enemy->GetLocation(), y, x);
	int lx;
	int ly;
	move_count += delta_second;
	if (move_count >= (1.0f / 4.0f))
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
			int i = GetRand(3);
			if (ret[eAdjacentDirection::UP] != ePanelID::WALL && i == 0)
			{
				now_direction = eEnemyDirectionState::UP;
			}
			else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL && i == 1)
			{
				now_direction = eEnemyDirectionState::RIGHT;
			}
			else if (ret[eAdjacentDirection::DOWN] != ePanelID::WALL && i == 2)
			{
				now_direction = eEnemyDirectionState::DOWN;
			}
			else if (ret[eAdjacentDirection::LEFT] != ePanelID::WALL && i == 3)
			{
				now_direction = eEnemyDirectionState::LEFT;
			}
		}
		move_count = 0.0f;
	}
}

void EnemyTypeBase::EscapeMove(float delta_second)
{
	std::vector<std::vector<ePanelID>> data;
	data = StageData::GetAll();
	int px, py;
	int gx, gy;

	for (py = 0; py < 31; py++)
	{
		for (px = 0; px < 28; px++)
		{
			if (data[py][px] == ePanelID::GATE)
			{
				gx = px;
				gy = py;
			}
		}
	}

	move_count += delta_second;
	if (move_count >= (1.0f / 16.0f))
	{	
		panel = StageData::GetPanelData(enemy->GetLocation());
		if (panel == ePanelID::BRANCH)
		{
			StageData::ConvertToIndex(enemy->GetLocation(), y, x);
			ret = StageData::GetAdjacentPanelData(enemy->GetLocation());
			int px = gx - x;
			int py = gy - y;
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
				if (gx < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (gx > x && ret[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
				else if (gy > y && ret[eAdjacentDirection::DOWN] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
				else if (ret[eAdjacentDirection::UP] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::UP;
				}
			}
			else
			{
				if (gy < y && ret[eAdjacentDirection::UP] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::UP;
				}
				else  if (gy > y && ret[eAdjacentDirection::DOWN] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::DOWN;
				}
				else if (gx < x && ret[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::LEFT;
				}
				else if (ret[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					now_direction = eEnemyDirectionState::RIGHT;
				}
			}
			move_count = 0.0f;
		}
	}
	if (panel == GATE)
	{
		enemy->SetLife(2);
		now_direction = eEnemyDirectionState::LEFT;
	}
}

void EnemyTypeBase::EscMonsterRoom(float delta_second)
{
	std::vector<std::vector<ePanelID>> data;

	data = StageData::GetAll();
	int px,py;
	int gx, gy;

	for (py = 0 ;py < 31; py++)
	{
		for (px = 0; px < 28; px++)
		{
			if (data[py][px] == ePanelID::GATE)
			{
				gx = px;
				gy = py;
			}
		}
	}
	x = (enemy->GetLocation().x - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE + 1;
	y = (enemy->GetLocation().y - (D_OBJECT_SIZE / 2.0f)) / D_OBJECT_SIZE + 1;
	panel = StageData::GetPanelData(enemy->GetLocation());
	enemy->SetMobility(eMobilityType::Stationary);
	if (gx == x)
	{	
		this->now_direction = eEnemyDirectionState::UP;
	}
	else
	{
		if (gx < x)
		{
			this->now_direction = eEnemyDirectionState::LEFT;
		}
		else
		{
			this->now_direction = eEnemyDirectionState::RIGHT;
		}		
	}
	if (panel == GATE && gx == x && gy == y)
	{
		enemy->SetMobility(eMobilityType::Movable);
		enemy->ChangeEnemyState(ePATROL);
		this->now_direction = eEnemyDirectionState::LEFT;
	}
}

void EnemyTypeBase::AttackMove(float delta_second, Player* playerdate)
{
	ret = StageData::GetAdjacentPanelData(enemy->GetLocation());
	panel = StageData::GetPanelData(enemy->GetLocation());
	StageData::ConvertToIndex(enemy->GetLocation(), y, x);
	enemy->SetPlayer(playerdate);
}