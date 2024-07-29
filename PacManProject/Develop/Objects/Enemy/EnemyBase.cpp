#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#include "Akabe.h"
#include "Pinky.h"
#include "Aosuke.h"
#include "Guzuta.h"

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
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	switch (enemy_type)
	{
	case AKABE:
		image = animation[0];
		break;
	case PINKY:
		image = animation[2];
		break;
	case AOSUKE:
		image = animation[4];
		break;
	case GUZUTA:
		image = animation[6];
		break;
	default:
		break;
	}
}

void EnemyBase::Update(float delta_second)
{

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{

}

void EnemyBase::AnimationControl(float delta_second)
{

}

void EnemyBase::Movement(float delta_second)
{

}

void EnemyBase::IdolMovement(float delta_second)
{

}

void EnemyBase::PatorolMove(float delta_second)
{

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
		enemy_type = eEnemyType::AKABE;
		break;
	case 1:
		enemy_type = eEnemyType::PINKY;
		break;
	case 2:
		enemy_type = eEnemyType::AOSUKE;
		break;
	case 3:
		enemy_type = eEnemyType::GUZUTA;
		break;
	default:
		break;
	}
}

void EnemyBase::SetPlayer(Player* object)
{
	this->player_date = object;
}