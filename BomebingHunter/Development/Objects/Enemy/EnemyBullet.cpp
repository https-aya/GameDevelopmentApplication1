#include "EnemyBullet.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() :anime_flag(FALSE),anime_count(0),anime_num(0),animation(NULL)
{

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/EnemyBullet/1.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/EnemyBullet/eff1.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/EnemyBullet/eff2.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/EnemyBullet/eff3.png");
	animation.push_back(tmp[0]);

	for (int i = 0; i < animation.size(); i++)
	{
		if (animation[i] == -1)
		{
			throw("“G‚Ì’e‚Ì‰æ‘œ%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}


	radian = 0.0;
	
	box_size = 16.0f;

	image = animation[0];

	score - 20;
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
	animation.clear();
	location = NULL;
	Delete = TRUE;
}

void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == ePlayer)
	{
		anime_flag = TRUE;
		box_size = NULL;
		direction = NULL;
	}
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
		if (anime_count >= 5)
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