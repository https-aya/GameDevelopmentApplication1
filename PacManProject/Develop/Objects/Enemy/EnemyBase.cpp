#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "Akabe.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : animation(), eyeanimation(), enemy_type(), enemy_state(), now_direction(), next_direction(), animation_count(NULL), animation_time(NULL)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	int lo_x = (location.x - (D_OBJECT_SIZE / 12));
	switch (lo_x)
	{
	case 14:
		enemy_type = AKABE;
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

void EnemyBase::Update(float)
{
	switch (enemy_type)
	{
	case AKABE:
		
	}
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
