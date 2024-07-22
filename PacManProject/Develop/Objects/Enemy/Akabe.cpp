#include "Akabe.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Akabe::Akabe()
{

}

Akabe::~Akabe()
{

}

void Akabe::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

}

