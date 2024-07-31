#include "Aosuke.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Aosuke::Aosuke(class EnemyBase* e)
{

}

Aosuke::~Aosuke()
{

}

void Aosuke::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	image = animation[4];
	z_layer = 6;
}

void Aosuke::Draw(const Vector2D& screen_offset, Vector2D loc) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = loc + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Aosuke::AttackMove(float delta_second)
{

}