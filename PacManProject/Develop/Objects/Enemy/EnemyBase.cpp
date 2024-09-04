#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h" 
#include "Factory/EnemyTypeFactory.h"
#include "DxLib.h"

#define ENEMY_SPEED (45.0f)

EnemyBase::EnemyBase()
	:velocity(0.0f)
	, enemy_type()
	, enemy_state()
	, hold_state()
	, world_time(0.0f)
	, flash_count(0)
	, izike_time(0.0f)
	, player(nullptr)
	, life()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{

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
	if (player->GetPowerUp() == true && life == 0)
	{
		if (enemy_state!=eEnemyState::eIZIKE)
		{
			hold_state = enemy_state;
		}
		enemy_state = eEnemyState::eIZIKE;
	}
	else if(life == 2 || life == 0)
	{
		enemy_state = hold_state;
		life = 0;
	}
	enemy_type->Update(delta_second,(this));
	location += velocity * ENEMY_SPEED * delta_second;
	if (location.x >= 640)
	{
		location.x = 1;
	}
	else if (location.x <= 0)
	{
		location.x = 639;
	}
	
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	enemy_type->Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	enemy_type->Finalize();
}

//void EnemyBase::PatorolMove(float delta_second)
//{
//	Vector2D point = 0.0f;
//	/*switch (enemy_type)
//	{
//	case eEnemyType::AKABE:
//		point = Vector2D(510.0f, 120.0f);
//		break;
//	case eEnemyType::PINKY:
//		point = Vector2D(100.0f, 120.0f);
//		break;
//	case eEnemyType::AOSUKE:
//		point = Vector2D(100.0f, 900.0f);
//		break;
//	case eEnemyType::GUZUTA:
//		point = Vector2D(600.0f, 900.0f);
//		break;
//	}*/
//	
//	std::map<eAdjacentDirection, ePanelID> ret = {
//		{ eAdjacentDirection::UP, ePanelID::NONE },
//		{ eAdjacentDirection::DOWN, ePanelID::NONE },
//		{ eAdjacentDirection::LEFT, ePanelID::NONE },
//		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
//	};
//
//	ret = StageData::GetAdjacentPanelData(this->location);
//
//	if (point.y < location.y)
//	{
//		if (ret[eAdjacentDirection::UP] != WALL)
//		{
//			now_direction = eEnemyDirectionState::UP;
//		}
//		else
//		{
//			if (point.x < location.x)
//			{
//				now_direction = eEnemyDirectionState::LEFT;
//			}
//			else
//			{
//				now_direction = eEnemyDirectionState::RIGHT;
//			}
//		}
//	}
//	else
//	{
//		now_direction = eEnemyDirectionState::DOWN;
//	}
//}

//void EnemyBase::AttackMove(float delta_second, Player* playerdate)
//{
//	//enemy->AttackMove(delta_second,playerdate);
//
//	std::map<eAdjacentDirection, ePanelID> ret = {
//		{ eAdjacentDirection::UP, ePanelID::NONE },
//		{ eAdjacentDirection::DOWN, ePanelID::NONE },
//		{ eAdjacentDirection::LEFT, ePanelID::NONE },
//		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
//	};
//
//	ret = StageData::GetAdjacentPanelData(this->location);
//
//	
//	Vector2D diff = player->GetLocation() - this->location;
//
//}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	Vector2D obj_loc = hit_object->GetLocation();

	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		player->SetEnemy(this);
		if (enemy_state == eEnemyState::eIZIKE)
		{
			life = 1;
			enemy_state = eEnemyState::eESCAPE;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
		}
	}	

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
	return enemy_state;
}

void EnemyBase::ChangeEnemyState(eEnemyState state)
{
	this->hold_state = state;
}

void EnemyBase::SetEnemytype()
{
	int x, y;
	StageData::ConvertToIndex(location, y, x);
	switch (x)
	{
	case 13:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AKABE);	
		hold_state = eEnemyState::ePATROL;
		break;
	case 12:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::AOSUKE);
		hold_state = eEnemyState::eIDLE;
		break;
	case 16:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::GUZUTA);
		hold_state = eEnemyState::eIDLE;
		break;
	case 14:
		enemy_type = EnemyTypeFactory::Get((*this), eEnemyType::PINKY);
		hold_state = eEnemyState::eIDLE;
		break;
	default:
		break;
	}
	enemy_state = hold_state;
}

void EnemyBase::SetPlayer(Player* object)
{
	this->player = object;
}

Player* EnemyBase::GetPlayer()
{
	return player;
}

void EnemyBase::SetVelocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void EnemyBase::SetMobility(eMobilityType mobility)
{
	this->mobility = mobility;
}

void EnemyBase::SetLife(int num)
{
	life = num;
}