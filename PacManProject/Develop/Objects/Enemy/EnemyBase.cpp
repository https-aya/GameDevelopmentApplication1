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
	, enemy()
	, enemy_state()
	, now_direction()
	, world_time(0.0f)
	, flash_count(0)
	, izike_time(0.0f)
	, player(nullptr)
	, animation_time(0.0f)
	, animation_count()
	, animation_num()
	, move_count(0.0f)
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
	z_layer = 6;
}

void EnemyBase::Update(float delta_second)
{
	Movement(delta_second);
	AnimationControl(delta_second);
	if (player->GetPowerUp() == true)
	{
		enemy_state = eEnemyState::eIZIKE;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	int eye_image = NULL;
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
	if (enemy_state != eEnemyState::eESCAPE)
	{
		__super::Draw(screen_offset);
	}
	if (enemy_state != eEnemyState::eIZIKE)
	{
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
}

void EnemyBase::Finalize()
{

}

void EnemyBase::AnimationControl(float delta_second)
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
			image = animation[16 + animation_count];
		}
		else 
		{
			image = animation[animation_num + animation_count];
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
	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE }
	};
	ret = StageData::GetAdjacentPanelData(this->location);

	move_count += delta_second;
	if (move_count >= (1.0f / 2.0f))
	{
		if (ret[eAdjacentDirection::UP] != WALL)
		{
			now_direction = eEnemyDirectionState::UP;
		}
		else if(ret[eAdjacentDirection::DOWN] != WALL)
		{
			now_direction = eEnemyDirectionState::DOWN;
		}
		move_count = 0;
	}

	switch (now_direction)
	{
	case eEnemyDirectionState::UP:
		velocity.y = -2.0f;
		break;
	case eEnemyDirectionState::DOWN:
		velocity.y = 2.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}
	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * ENEMY_SPEED * delta_second;
}

void EnemyBase::PatorolMove(float delta_second)
{
	Vector2D point = 0.0f;
	switch (enemy_type)
	{
	case eEnemyType::AKABE:
		point = Vector2D(600.0f, 120.0f);
		break;
	case eEnemyType::PINKY:
		point = Vector2D(100.0f, 120.0f);
		break;
	case eEnemyType::AOSUKE:
		point = Vector2D(100.0f, 800.0f);
		break;
	case eEnemyType::GUZUTA:
		point = Vector2D(600.0f, 800.0f);
		break;
	}
		
	//DrawCircleAA(point.x, point.y, 5.0, 4, 0x000000, 1);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE },
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	ret = StageData::GetAdjacentPanelData(this->location);

	Vector2D diff = point - location;
	

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
		enemy_type = enemy->GetEnemytype();
		animation_num = 0;
		enemy_state = eEnemyState::ePATROL;
		break;
	case 1:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::AOSUKE);
		now_direction = eEnemyDirectionState::UP;
		enemy_type = enemy->GetEnemytype();
		animation_num = 4;
		enemy_state = eEnemyState::eIDLE;
		break;
	case 2:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::GUZUTA);
		now_direction = eEnemyDirectionState::UP;
		enemy_type = enemy->GetEnemytype();
		animation_num = 6;
		enemy_state = eEnemyState::eIDLE;
		break;
	case 3:
		enemy = EnemyTypeFactory::Get((*this), eEnemyType::PINKY);
		now_direction = eEnemyDirectionState::DOWN;
		enemy_type = enemy->GetEnemytype();
		animation_num = 2;
		enemy_state = eEnemyState::eIDLE;
		break;
	default:
		break;
	}
	image = animation[animation_num];
}

void EnemyBase::SetPlayer(Player* object)
{
	this->player = object;
}

eEnemyType EnemyBase::GetEnemytype() const
{
	return this->enemy_type;
}