#include "EnemyTypeBase.h"
#include "../../Utility/ResourceManager.h" 
#include "DxLib.h"

void EnemyTypeBase::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
}

void EnemyTypeBase::Update(float delta_second)
{
	Movement(delta_second);
	AnimationControl(delta_second);
}

void EnemyTypeBase::AnimationControl(float delta_second)
{
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_count += 1;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		animation_time = 0.0f;
		if (enemy_state == eEnemyState::eIZIKE)
		{
			switch (flash_count)
			{
			case 1:
				flash_count += 1;
			case 0:
				image = animation[16 + animation_count];
				break;
			case 2:
				image = animation[18 + animation_count];
				flash_count += -1;
				break;
			}
		}
		else
		{
			image = animation[animation_num + animation_count];
		}
	}
}