#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "Factory/EnemyTypeFactory.h"
#include "DxLib.h"

#define ENEMY_SPEED (45.0f)

EnemyBase::EnemyBase()
	: animation()
	, eyeanimation()
	, velocity(0.0f)
	, enemy_type()
	, enemy_state()
	, now_direction()
	, world_time(0.0f)
	, flash_count(0)
	, izike_time(0.0f)
	, player_date(nullptr)
	, animation_time(0.0f)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	
}

void EnemyBase::Update(float delta_second)
{
	Movement(delta_second);
	AnimationControl(delta_second);
}

void EnemyBase::Draw(const Vector2D& screen_offset, Vector2D loc) const
{
	enemy_type->Draw(screen_offset , this->location);
}

void EnemyBase::Finalize()
{

}

void EnemyBase::AnimationControl(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		/*animation_time = 0.0f;
		switch (enemy_type)
		{
		case AKABE:
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
			break;
		case PINKY:
			if (image == animation[2])
			{
				image = animation[3];
			}
			else
			{
				image = animation[2];
			}
			break;
		case AOSUKE:
			if (image == animation[4])
			{
				image = animation[5];
			}
			else
			{
				image = animation[4];
			}
			break;
		case GUZUTA:
			if (image == animation[6])
			{
				image = animation[7];
			}
			else
			{
				image = animation[6];
			}
			break;*/
		/*}*/
	}
}

void EnemyBase::Movement(float delta_second)
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
		AttackMove(delta_second);
		break;
	case eESCAPE:
		EscapeMove(delta_second);
		break;
	case eIZIKE:
		IzikeMove(delta_second);
		break;
	}
}

void EnemyBase::IdolMove(float delta_second)
{

}

void EnemyBase::PatorolMove(float delta_second)
{
	Vector2D point = 0.0f;

	

	Vector2D diff = point - location;
	if (diff.x >= 10)
	{
		now_direction = eEnemyDirectionState::RIGHT;
	}
	else if(diff.x <= 8)
	{
		now_direction = eEnemyDirectionState::LEFT;
	}
	else if (diff.y <= 10)
	{
		now_direction = eEnemyDirectionState::UP;
	}
	else if (diff.y >= 8)
	{
		now_direction = eEnemyDirectionState::DOWN;
	}

	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		velocity.y = -2.0f;
		break;
	case eEnemyDirectionState::DOWN:
		velocity.y = 2.0f;
		break;
	case eEnemyDirectionState::LEFT:
		velocity.x = -2.0f;
		break;
	case eEnemyDirectionState::RIGHT:
		velocity.x = 2.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}
	// ˆÚ“®—Ê * ‘¬‚³ * ŽžŠÔ ‚ÅˆÚ“®æ‚ðŒˆ’è‚·‚é
	location += velocity * ENEMY_SPEED * delta_second;
}

void EnemyBase::IzikeMove(float delta_second)
{

}

void EnemyBase::EscapeMove(float delta_second)
{

}

void EnemyBase::AttackMove(float delta_second)
{

}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{

}

eEnemyState EnemyBase::GetEnemyState()
{
	return  this->enemy_state;
}

void EnemyBase::ChangeEnemyState(eEnemyState state)
{
	this->enemy_state = state;
}

void EnemyBase::SetEnemytype(int count)
{
	switch (count)
	{
	case 0:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AKABE);
		now_direction = eEnemyDirectionState::LEFT;
		enemy_state = eEnemyState::ePATROL;
		break;
	case 1:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AOSUKE);
		now_direction = eEnemyDirectionState::UP;
		break;
	case 2:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::GUZUTA);
		now_direction = eEnemyDirectionState::UP;
		break;
	case 3:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::PINKY);

		now_direction = eEnemyDirectionState::DOWN;
		break;
	default:
		break;
	}
}

void EnemyBase::SetPlayer(Player* object)
{
	this->player_date = object;
}