#include "FlyText.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

FlyText::FlyText():digit_size(0),number_image(NULL),score(0)
{
	for (int i = 0; i < 3; i++)
	{
		fly_text_digit[i] = NULL;
	}
}

FlyText::~FlyText()
{
	Finalize();
}

void FlyText::Initialize()
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
	

	for (int i = 0; i < number_image.size(); i++)
	{
		if (number_image[i] == -1)
		{
			throw("ƒXƒRƒA%d‚ª‚ ‚è‚Ü‚¹‚ñ", i);
		}
	}
}

void FlyText::SetFlyText(int ft)
{
	score = ft;
	if (ft != 0)
	{
		if (ft < 0)
		{
			ft *= -1;
		}
		for (int i = 0; i < 3; i++)
		{
			fly_text_digit[i] = 0;
			if (ft < 1)
			{
				break;
			}
			else
			{
				fly_text_digit[i] = ft % 10;
				ft = ft / 10;
				digit_size++;
			}
		}
	}
	else
	{
		fly_text_digit[0] = 0;
	}
}

void FlyText::Draw(Vector2D location) const
{
	if (score < 0)
	{
		DrawRotaGraph(location.x + 24, location.y, 1.0, 0.0, number_image[10], TRUE);
		for (int i = digit_size - 1; i >= 0; i--)
		{
			DrawRotaGraph((location.x + 48) - 12 * i, location.y, 1.0, 0.0, number_image[fly_text_digit[i]], TRUE);
		}
	}
	else
	{
		for (int i = digit_size - 1; i >= 0; i--)
		{
			DrawRotaGraph((location.x + 48) - 12 * i, location.y, 1.0, 0.0, number_image[fly_text_digit[i]], TRUE);
		}
	}
}

void FlyText::Finalize()
{
	number_image.clear();
}