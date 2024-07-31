#include "Akabe.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Akabe::Akabe(class EnemyBase* e)
{

}

Akabe::~Akabe()
{

}

void Akabe::Initialize()
{	
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;
	image = animation[0];
	z_layer = 6;
}

void Akabe::Draw(const Vector2D& screen_offset , Vector2D loc) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = loc + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Akabe::AttackMove(float delta_second)
{

}

