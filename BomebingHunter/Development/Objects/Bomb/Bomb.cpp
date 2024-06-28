#include "Bomb.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"

Bomb::Bomb() : anime_flag(false),anime_count(0),anime_num(0),animation(NULL)
{
}

Bomb :: ~Bomb()
{

}

void Bomb::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Bomb/Bomb.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/1.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/2.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/3.png");
	animation.push_back(tmp[0]);


	for (int i = 0; i < animation.size(); i++)
	{
		if (animation[i] == -1)
		{
			throw("ボムの画像%dがありません",i);
		}
	}

	radian = 90 * (3.14 / 180);

	box_size = 32.0;

	SetDirection(Vector2D(0.0f, 2.0f));

	image = animation[0];
}

void Bomb::Update()
{
	Movement();

	AnimeControl();

}

void Bomb::Draw() const
{

	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE);
	DrawFormatString(50, 50, 0xffffff, "%d", anime_flag);
	__super::Draw();
}

void Bomb::Finalize()
{
	location = NULL;
	Delete = TRUE;
	animation.clear();
}

void Bomb::OnHitCollision(GameObject* hit_object)
{
	char ty = hit_object->GetType();
	if (ty == ePlayer)
	{
		if (hit_object->GetDirection().x > 0)
		{
			radian = 0;
			direction.x = 2.0f;
		}
		else if (hit_object->GetDirection().x < 0)
		{
			radian = 180 * (3.14 / 180);
			direction.x = -2.0f;
		}
	}
	if (ty != ePlayer && ty != eBome && ty != eEnemyBullet)
	{
		anime_flag = true;
		direction = 0.0f;
		box_size = NULL;
	}

}

void Bomb::Movement()
{

	if (radian < 90 * (3.14 / 180))
	{
		radian += 0.5 * (3.14 / 180);
		direction.x -= (float)0.01;
	}
	else if (radian > 90 * (3.14 / 180))
	{
		radian -= 0.5 * (3.14 / 180);
		direction.x += (float)0.01;
	}


	location += direction;
	if (location.y >= 400)
	{
		direction = 0.0f;
		anime_flag = true;
		box_size = NULL;

	}
}

void Bomb::AnimeControl()
{
	if (anime_flag == true)
	{
		anime_count++;
		if (anime_count >= 10)
		{
			radian = 0;
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