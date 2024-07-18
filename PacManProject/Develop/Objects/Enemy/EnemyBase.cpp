#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#include "Akabe.h"

EnemyBase::EnemyBase() : animation(), eyeanimation(), enemy_type(), enemy_state(), now_direction(), next_direction(), animation_count(NULL), animation_time(NULL), enemy()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	enemy->Initialize();
}

void EnemyBase::Update(float)
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

void EnemyBase::EnemyTypeChange(int x)
{
	switch (x)
	{
	case 14:
		enemy = dynamic_cast<EnemyBase*>(new Akabe);
		break;
	case 13:
		enemy_type = AOSUKE;
		break;
	case 15:
		enemy_type = PINKY;
		break;
	case 17:
		enemy_type = GUZUTA;
		break;
	}
}