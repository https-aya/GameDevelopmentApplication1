#include "Score.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

Score::Score() :  score(0),high_score(0),number_image(NULL),font_image(NULL),score_digit_size(0),high_score_digit_size(0),time(0),count_time(0)
{
	for (int i = 0; i < 10; i++)
	{
		score_digit[i] = NULL;
		high_score_digit[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		time_digit[i] = NULL;
	}
	
}

Score::~Score()
{
	Finalize();
}

void Score::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Score/0.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/1.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/2.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/3.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/4.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/5.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/6.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/7.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/8.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/9.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/FlyText/-.png");
	number_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/font-21.png");
	font_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Score/hs.png");
	font_image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/TimeLimit/timer-03.png");
	font_image.push_back(tmp[0]);

	for (int i = 0; i < font_image.size(); i++)
	{
		if (font_image[i] == -1)
		{
			throw("フォントイメージ%dがありません", i);
		}
	}

	for (int i = 0; i < number_image.size(); i++)
	{
		if (number_image[i] == -1)
		{
			throw("スコア%dがありません", i);
		}
	}

	score = 0;
	time = 60;
}

void Score::Update()
{
	count_time++;
	if (count_time >= FLAME_RATE)
	{
		time--;
		count_time = 0;
	}
	score_digit_size = 0;
	int sco = score;
	int times = time;
	//スコアを桁ごとに保存
	for (int i = 0; i < 10; i++)
	{
		if (sco == 0)
		{
			score_digit[0] = sco;
			break;
		}
		 if (sco < 1) 
		{
			break;
		}
		else
		{
			score_digit_size++;
			score_digit[i] = sco % 10;
			sco = sco / 10;
		}
	}
	//時間を桁ごとに保存
	for (int i = 0; i < 2; i++)
	{
		time_digit[i] = 0;
		if (times == 0)
		{
			time_digit[0] = time;
			break;
		}
		if (time < 1)
		{
			break;
		}
		else
		{
			time_digit[i] = times % 10;
			times = times / 10;
		}
	}
}

void Score::Draw() const
{
	DrawRotaGraph(240, 460, 1.0, 0.0, font_image[0], TRUE);
	DrawRotaGraph(440, 460, 1.0, 0.0, font_image[1], TRUE);
	DrawRotaGraph(30, 460, 0.5, 0.0, font_image[2], TRUE);
	//スコアを画像で描画
	if (score_digit_size != 0)
	{
		for (int i = 0; i < score_digit_size; i++)
		{
			DrawRotaGraph(280 + 12 * i, 460, 1.0, 0.0, number_image[score_digit[score_digit_size - i - 1]], TRUE);
		}
	}
	else
	{
		DrawRotaGraph(292, 460, 1.0, 0.0, number_image[score_digit[0]], TRUE);
	}
	//ハイスコアを画像で描画
	if (high_score_digit_size != 0)
	{
		for (int i = 0; i < high_score_digit_size; i++)
		{
			DrawRotaGraph(490 + 12 * i, 460, 1.0, 0.0, number_image[high_score_digit[high_score_digit_size - i - 1]], TRUE);
		}
	}
	else
	{
		DrawRotaGraph(502, 460, 1.0, 0.0, number_image[high_score_digit[0]], TRUE);
	}
	//時間を画像で描画
	for (int i = 1; i >= 0; i--)
	{
		DrawRotaGraph(62 - 12 * i, 460, 1.0,0.0, number_image[time_digit[i]], TRUE);
	}
}

void Score::Finalize()
{
	for (int i = 0; i < 10; i++)
	{
		score_digit[i] = NULL;
	}
	number_image.clear();
	font_image.clear();
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
		high_score_digit_size = 0;
		int hsco = high_score;
		//ハイスコアを桁ごとに保存
		for (int i = 0; i < 10; i++)
		{
			if (hsco == 0)
			{
				high_score_digit[0] = hsco;
				break;
			}
			if (hsco < 1)
			{
				break;
			}
			else
			{
				high_score_digit_size++;
				high_score_digit[i] = hsco % 10;
				hsco = hsco / 10;
			}
		}
	}
}

int Score::GetTime() const
{
	return time;
}