#include "TimeUp.h"
#include "DxLib.h"

TimeUp::TimeUp() 
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
}
