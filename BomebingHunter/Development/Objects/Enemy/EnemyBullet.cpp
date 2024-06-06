#include "EnemyBullet.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() :anime_flag(FALSE),anime_count(0),anime_num(0)
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

	SetDirection(Vector2D(0.0f, -1.0f));

	radian = 0.0;
	
	box_size = 16.0f;

	image = animation[0];
}

void EnemyBullet::Update()
{
	Movement();

	AnimeControl();

	if ((location.x < box_size.x) || (location.x > box_size.x + 640) || (location.y < box_size.y))
	{
		Finalize();
	}
}

void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE);
	__super::Draw();
}

void EnemyBullet::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
	location = NULL;
	Delete = TRUE;
}

void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	anime_flag = TRUE;
	box_size = NULL;
	direction = NULL;
}

void EnemyBullet::Movement()
{
	location += direction;
}

void EnemyBullet::AnimeControl()
{
	if (anime_flag == TRUE)
	{
		anime_count++;
		if (anime_count >= 10)
		{
			anime_num++;
			if (anime_num < 4)
			{
				image = animation[anime_num];
			}
			else
			{
				Finalize();
			}
			anime_count = 0;
		}
	}
}