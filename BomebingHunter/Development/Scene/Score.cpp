#include "Score.h"
#include "DxLib.h"

Score::Score(): score_size(0) 
{
	for (int i = 0; i < 10; i++)
	{
		score_image[i] = NULL;
		score[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		font_image[i] = NULL;
	}
}

Score::~Score()
{
	Finalize();
}

void Score::Initialize()
{
	score_image[0] = LoadGraph("Resource/Images/Score/0.png");
	score_image[1] = LoadGraph("Resource/Images/Score/1.png");
	score_image[2] = LoadGraph("Resource/Images/Score/2.png");
	score_image[3] = LoadGraph("Resource/Images/Score/3.png");
	score_image[4] = LoadGraph("Resource/Images/Score/4.png");
	score_image[5] = LoadGraph("Resource/Images/Score/5.png");
	score_image[6] = LoadGraph("Resource/Images/Score/6.png");
	score_image[7] = LoadGraph("Resource/Images/Score/7.png");
	score_image[8] = LoadGraph("Resource/Images/Score/8.png");
	score_image[9] = LoadGraph("Resource/Images/Score/9.png");
	font_image[0] = LoadGraph("Resource/Images/Score/font-21.png");
	font_image[1] = LoadGraph("Resource/Images/Score/hs.png");

	for (int i = 0; i < 10; i++)
	{
		if (score_image[i] == -1)
		{
			throw("ƒXƒRƒA%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}
}

void Score::Update(int scr)
{
	score_size = 0;
	for (int i = 0; i < 10; i++)
	{
		if (scr == 0)
		{
			score[0] = scr;
			break;
		}
		 if (scr < 1) 
		{
			break;
		}
		else
		{
			score_size++;
			score[i] = scr % 10;
			scr = scr / 10;
		}
	}
}

void Score::Draw() const
{
	DrawRotaGraph(250, 460, 1.0, 0.0, font_image[0], TRUE);
	if (score_size != 0)
	{
		for (int i = 0; i < score_size; i++)
		{
			DrawRotaGraph(280 + 10 * i, 460, 1.0, 0.0, score_image[score[score_size - i - 1]], TRUE);
		}
	}
	else
	{
		DrawRotaGraph(290, 460, 1.0, 0.0, score_image[score[0]], TRUE);
	}

}

void Score::Finalize()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(score_image[i]);
		score[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(font_image[i]);
	}
}