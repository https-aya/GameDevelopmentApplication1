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
	tmp = rm->GetImages("Resource/Images/Evaluation/BAD.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/Finish.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/GOOD.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/OK.png");
	image.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Evaluation/Perfect.png");
	image.push_back(tmp[0]);

	for (int i = 0; i < image.size(); i++)
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
	image.clear();
}