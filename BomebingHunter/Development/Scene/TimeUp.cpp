#include "TimeUp.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"
#include <chrono>
#include <thread>

TimeUp::TimeUp() :draw(NULL),count(0),image(NULL)
{

}

TimeUp::~TimeUp()
{
}

void TimeUp::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Evaluation/Finish.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/BAD.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/GOOD.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/OK.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/Perfect.png");
	image.push_back(tmp[0]);
	
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/BGM_timeup.wav");
	sound.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/SE_bad.wav");
	sound.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/SE_good.wav");
	sound.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/SE_ok.wav");
	sound.push_back(tmp[0]);
	tmp = rm->GetSounds("Resource/Sounds/Evaluation/SE_perfect.wav");
	sound.push_back(tmp[0]);

	for (int i = 0; i < image.size(); i++)
	{
		if (image[i] == -1)
		{
			throw("評価%dがありません", i);
		}
	}

	for (int i = 0; i < sound.size(); i++)
	{
		if (sound[i] == -1)
		{
			throw("評価音源%dがありません", i);
		}
	}

	draw = image[0];

	count = 300;
}

void TimeUp::Update(int sco)
{
	
	count--;
	if (count < 0)
	{
		count = 0;
	}
	else
	{
		if (CheckSoundMem(sound[0]) != true)
		{
			PlaySoundMem(sound[0], DX_PLAYTYPE_LOOP, TRUE);
		}
		if (count == 1)
		{
			//スコアに応じて画面に表示するものを変更する
			if (sco >= 1500)
			{
				PlaySoundMem(sound[4], DX_PLAYTYPE_BACK, TRUE);
				draw = image[4];
			}
			else if (sco >= 1000)
			{
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK, TRUE);
				draw = image[2];
			}
			else if (sco >= 500)
			{
				PlaySoundMem(sound[3], DX_PLAYTYPE_BACK, TRUE);
				draw = image[3];
			}
			else
			{
				PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
				draw = image[1];
			}
		}
	}
}

void TimeUp::Draw() const
{
	DrawRotaGraph(320, 240, 1.0, 0.0, draw, TRUE);
}

void TimeUp::Finalize()
{
	for (int i = 0; i < sound.size(); i++)
	{
		if (CheckSoundMem(sound[i]) == true)
		{
			StopSoundMem(sound[i]);
		}
	}
	//動的配列の開放
	image.clear();
	sound.clear();
}