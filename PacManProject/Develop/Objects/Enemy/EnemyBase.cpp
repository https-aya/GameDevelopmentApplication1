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
	switch (enemy_type)
	{
	case AKABE:
		Akabe::Initialize;
		break;
	case PINKY:
		Pinky::Initialize;
		break;
	case AOSUKE:
		Aosuke::Initialize;
		break;
	case GUZUTA:
		Guzuta::Initialize;
		break;
	}
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

void EnemyBase::ChangeEnemyType(int location)
{
	switch (location)
	{
	case 13:
		enemy_type = eEnemyType::AKABE;
		break;
	case 14:
		enemy_type = eEnemyType::PINKY;
		break;
	case 15:
		enemy_type = eEnemyType::AOSUKE;
		break;
	case 17:
		enemy_type = eEnemyType::GUZUTA;
		break;
	}
}