#include "Score.h"
#include "DxLib.h"

Score::Score() :  score(0),high_score(0)
{
	for (int i = 0; i < 10; i++)
	{
		score_image[i] = NULL;
		scores[i] = NULL;
		high_scores[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		font_image[i] = NULL;
		score_size[i] = NULL;
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

	score = 0;
}

void Score::Update()
{
	score_size[0] = 0;
	int sco = score;
	for (int i = 0; i < 10; i++)
	{
		if (sco == 0)
		{
			scores[0] = sco;
			break;
		}
		 if (sco < 1) 
		{
			break;
		}
		else
		{
			score_size[0]++;
			scores[i] = sco % 10;
			sco = sco / 10;
		}
	}
}

void Score::Draw() const
{
	DrawRotaGraph(240, 460, 1.0, 0.0, font_image[0], TRUE);
	if (score_size != 0)
	{
		for (int i = 0; i < score_size[0]; i++)
		{
			DrawRotaGraph(280 + 12 * i, 460, 1.0, 0.0, score_image[scores[score_size[0] - i - 1]], TRUE);
		}
	}
	else
	{
		DrawRotaGraph(292, 460, 1.0, 0.0, score_image[scores[0]], TRUE);
	}

}

void Score::Finalize()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(score_image[i]);
		scores[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(font_image[i]);
	}
}

void Score::SetScore(int scr)
{
	score += scr;
	if (score < 0)
	{
		score = 0;
	}
}

int Score::GetScore() const
{
	return score;
}

void Score::SetHighScore()
{
	if (high_score < score)
	{
		high_score = score;
		score_size[1] = 0;
		int hsco = high_score;
		for (int i = 0; i < 10; i++)
		{
			if (hsco == 0)
			{
				high_scores[0] = hsco;
				break;
			}
			if (hsco < 1)
			{
				break;
			}
			else
			{
				score_size[1]++;
				high_scores[i] = hsco % 10;
				hsco = hsco / 10;
			}
		}
	}
}