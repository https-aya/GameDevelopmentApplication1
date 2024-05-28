#include "Blast.h"
#include "DxLib.h"

Blast::Blast() :anime_count(0), anime_num(0), location(0.0f)
{
	for (int i = 0; i < 3; i++)
	{
		animation[i] = NULL;
	}
}

Blast::~Blast()
{
}

void Blast::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Blast/1.png");
	animation[1] = LoadGraph("Resource/Images/Blast/2.png");
	animation[2] = LoadGraph("Resource/Images/Blast/3.png");

	for (int i = 0; i < 3; i++)
	{
		if (animation[i] == -1)
		{
			throw("Blast%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}

	image = animation[0];

	radian = 0.0;
}

void Blast::Update()
{
	AnimeControl();
}

void Blast::Draw() const
{
	DrawRotaGraph(location.x, location.y, 0.5, radian, image, TRUE);
}

void Blast::Finalize()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(animation[i]);
	}
}

void Blast::AnimeControl()
{
	anime_count++;
	if (anime_count >= 30)
	{
		anime_num++;
		image = animation[anime_num];
		if (anime_num >= 3)
		{
			Finalize();
		}
		anime_count++;
	}
}