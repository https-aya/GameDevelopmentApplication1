#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/StageData.h"
#include "Factory/EnemyTypeFactory.h"
#include "DxLib.h"

#define ENEMY_SPEED (45.0f)

EnemyBase::EnemyBase()
	: animation()
	, eyeanimation()
	, velocity(0.0f)
	, enemy_type()
	, enemy()
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

	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	Movement(delta_second);
	AnimationControl(delta_second);
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{

}

void EnemyBase::AnimationControl(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		switch (enemy->GetEnemytype())
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
		case GUZUTA:
			if (image == animation[6])
			{
				image = animation[7];
			}
			else
			{
				image = animation[6];
			}
			break;
		}
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

	StageData::GetAdjacentPanelData

	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		velocity.y = -1.0f;
		break;
	case eEnemyDirectionState::DOWN:
		velocity.y = 1.0f;
		break;
	case eEnemyDirectionState::LEFT:
		velocity.x = -1.0f;
		break;
	case eEnemyDirectionState::RIGHT:
		velocity.x = 1.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}
	// 移動量 * 速さ * 時間 で移動先を決定する
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
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}
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
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::AKABE);
		now_direction = eEnemyDirectionState::LEFT;
		image = animation[0];
		enemy_state = eEnemyState::ePATROL;
		break;
	case 1:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::AOSUKE);
		now_direction = eEnemyDirectionState::UP;
		image = animation[4];
		break;
	case 2:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::GUZUTA);
		now_direction = eEnemyDirectionState::UP;
		image = animation[6];
		break;
	case 3:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::PINKY);
		now_direction = eEnemyDirectionState::DOWN;
		image = animation[2];
		break;
	default:
		break;
	}
}

void EnemyBase::SetPlayer(Player* object)
{
	this->player_date = object;
}

eEnemyType EnemyBase::GetEnemytype() const
{
	return this->enemy_type;
}