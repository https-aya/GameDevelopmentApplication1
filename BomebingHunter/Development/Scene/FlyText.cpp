#include "FlyText.h"
#include "DxLib.h"

FlyText::FlyText():size(0)
{
	for (int i = 0; i < 11; i++)
	{
		number_image[i] = NULL;
	}
	for (int i = 0; i < 3; i++)
	{
		fly_text[i] = NULL;
	}
}

FlyText::~FlyText()
{
	Finalize();
}

void FlyText::Initialize()
{
	number_image[0] = LoadGraph("Resource/Images/Score/0.png");
	number_image[1] = LoadGraph("Resource/Images/Score/1.png");
	number_image[2] = LoadGraph("Resource/Images/Score/2.png");
	number_image[3] = LoadGraph("Resource/Images/Score/3.png");
	number_image[4] = LoadGraph("Resource/Images/Score/4.png");
	number_image[5] = LoadGraph("Resource/Images/Score/5.png");
	number_image[6] = LoadGraph("Resource/Images/Score/6.png");
	number_image[7] = LoadGraph("Resource/Images/Score/7.png");
	number_image[8] = LoadGraph("Resource/Images/Score/8.png");
	number_image[9] = LoadGraph("Resource/Images/Score/9.png");
	number_image[10] = LoadGraph("Resource/Images/FlyText/-.png");

	for (int i = 0; i < 11; i++)
	{
		if (number_image[i] == -1)
		{
			throw("ƒXƒRƒA%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}
}

void FlyText::SetFlyText(int ft)
{
	int fly = ft;

	if (fly < 0)
	{
		fly *= -1;
	}
	for (int i = 0; i < 3; i++)
	{
		fly_text[i] = 0;
		if (fly < 1)
		{
			break;
		}
		else
		{
			fly_text[i] = fly % 10;
			fly = fly / 10;
			size++;
		}
	}
}

void FlyText::Draw(Vector2D location, int sco) const
{
	if (sco < 0)
	{
		DrawRotaGraph(location.x + 12, location.y, 1.0, 0.0, number_image[10], TRUE);
		for (int i = size - 1; i >= 0; i--)
		{
			DrawRotaGraph((location.x + 48) - 12 * i, location.y, 1.0, 0.0, number_image[fly_text[i]], TRUE);
		}
	}
	else
	{
		for (int i = size - 1; i >= 0; i--)
		{
			DrawRotaGraph((location.x + 48) - 12 * i, location.y, 1.0, 0.0, number_image[fly_text[i]], TRUE);
		}
	}
}

void FlyText::Finalize()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number_image[i]);
	}
}