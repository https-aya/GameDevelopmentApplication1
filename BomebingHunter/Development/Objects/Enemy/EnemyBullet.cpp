#include "EnemyBullet.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() : direction(NULL)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");

	direction = Vector2D(0.1f, 0.0f);

	radian = 0.0;
	
	box_size = 32.0f;

	image = animation[0];
}

void EnemyBullet::Update()
{
	Movement();
}

void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);
	__super::Draw();
}

void EnemyBullet::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	box_size = 0.0f;
	direction = 0.0f;
	location = NULL;
}

void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	Finalize();
}

void EnemyBullet::Movement()
{
	location += direction;
}