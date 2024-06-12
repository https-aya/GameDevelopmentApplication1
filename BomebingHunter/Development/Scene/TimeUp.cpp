#include "TimeUp.h"
#include "DxLib.h"
#include <chrono>
#include <thread>

TimeUp::TimeUp() :draw(NULL),count(0)
{
	for (int i = 0; i < 5; i++)
	{
		image[i] = NULL;
	}
}

TimeUp::~TimeUp()
{
}

void TimeUp::Initialize()
{
	image[0] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	image[1] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	image[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	image[3] = LoadGraph("Resource/Images/Evaluation/OK.png");
	image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	for (int i = 0; i < 5; i++)
	{
		if (image[i] == -1)
		{
			throw("•]‰¿%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}

	draw = image[1];

	count = 300;
}

void TimeUp::Update(int sco)
{

	count--;
	if (count <= 0)
	{
		if (sco >= 1500)
		{
			draw = image[4];
		}
		else if (sco >= 1000)
		{
			draw = image[2];
		}
		else if (sco >= 500)
		{
			draw = image[3];
		}
		else
		{
			draw = image[0];
		}
	}
	if (count < 0)
	{
		count = 0;
	}
}

void TimeUp::Draw() const
{
	DrawRotaGraph(320, 240, 1.0, 0.0, draw, TRUE);
}

void TimeUp::Finalize()
{
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(image[i]);
	}
}