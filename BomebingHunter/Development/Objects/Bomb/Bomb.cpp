#include "Bomb.h"
#include "DxLib.h"

Bomb::Bomb() : anime_flag(false),anime_count(0),anime_num(0),sound(), anim_location(0.0f)
{
}

Bomb :: ~Bomb()
{

}

void Bomb::Initialize()
{

	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Bomb/Bomb.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/1.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/2.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Blast/3.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/explosion.wav");
	sound = tmp[0];

	for (int i = 0; i < animation.size(); i++)
	{
		if (animation[i] == -1)
		{
			throw("ボムの画像%dがありません",i);
		}
	}

	if (sound == -1)
	{
		throw("explosionのサウンドがありません");
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
	if (anime_flag == FALSE)
	{
		DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE);
	}
	else
	{
		DrawRotaGraphF(anim_location.x, anim_location.y, 0.5, radian, image, TRUE);
	}
}

void Bomb::Finalize()
{
	location = NULL;
	Delete = TRUE;
	animation.clear();
	DeleteSoundMem(sound);
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

	if (anime_flag == FALSE)
	{
		location += direction;
	}
	
	if (location.y >= 400)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);
		anim_location = location;
		location = NULL;
		direction = 0.0f;
		anime_flag = TRUE;
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