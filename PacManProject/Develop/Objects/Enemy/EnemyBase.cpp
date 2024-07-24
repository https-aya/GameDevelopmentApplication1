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
	, player_date()
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

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{

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