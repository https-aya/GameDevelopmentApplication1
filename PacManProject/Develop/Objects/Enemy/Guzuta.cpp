#include "Guzuta.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Guzuta::Guzuta(class EnemyBase* e)
{

}

Guzuta::~Guzuta()
{

}

void Guzuta::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// “–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	image = animation[6];
	z_layer = 6;
}

void Guzuta::AttackMove(float delta_second)
{

}

int Guzuta::GetImage() const
{
	return this->image;
}