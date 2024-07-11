#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : animation(), eyeanimation(), enemy_type(), enemy_state(), now_direction(), next_direction(), animation_count(NULL), animation_time(NULL), enemy()
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
	CreateObject<Enemy>();
}

void EnemyBase::Update(float)
{
	for (Enemy* obj : enemy)
	{
		obj->Update();
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	for (Enemy* obj : enemy)
	{
		obj->Draw(screen_offset);
	}
}

void EnemyBase::Finalize()
{

}

void EnemyBase::AnimationControl(float delta_second)
{

}
