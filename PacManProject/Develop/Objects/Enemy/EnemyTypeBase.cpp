#include "EnemyTypeBase.h"
#include "../../Utility/ResourceManager.h" 
#include "EnemyBase.h"
#include "DxLib.h"

EnemyTypeBase::EnemyTypeBase(class EnemyBase* e) : enemy(e)
{

}

void EnemyTypeBase::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
}

void EnemyTypeBase::Update(float delta_second ,eEnemyState state)
{
	enemy_state = state;
	Movement(delta_second);
	AnimationControl(delta_second);
}

void EnemyTypeBase::Draw(const Vector2D& screen_offset) const
{
	if (enemy_state != eEnemyState::eESCAPE)
	{
		Vector2D graph_location = this->enemy->GetLocation() + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
	if (enemy_state != eEnemyState::eIZIKE)
	{
		Vector2D graph_location = this->enemy->GetLocation() + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
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
			image = animation[animation_num + animation_count];
		}
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
}