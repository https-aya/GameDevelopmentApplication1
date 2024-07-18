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
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eyeanimation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;


	switch (enemy_type)
	{
	case AKABE:
		image = animation[0];
		break;
	case PINKY:
		image = animation[2];
		break;
	case AOSUKE:
		image = animation[4];
		break;
	case GUZUTA:
		image = animation[6];
	}

	enemy_state = eIDLE;
	z_layer = 6;
}

void Akabe::Update()
{
	switch (enemy_state)
	{
	case eIDLE:
		IdleMove();
		break;
	case ePATROL:
		PatrolMove();
		break;
	case eATTACK:
		AttackMove();
		break;
	case eIZIKE:
		IzikeMove();
		break;
	case eESCAPE:
		EscapeMove();
		break;
	}
}

void Akabe::Draw(const Vector2D& screen_offset) const
{
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Akabe::Finalize()
{
	animation.clear();
	eyeanimation.clear();
}

void Akabe::IdleMove()
{
	
}

void Akabe::AttackMove()
{

}

void Akabe::PatrolMove()
{

}

void Akabe::IzikeMove()
{

}

void Akabe::EscapeMove()
{

}

void Akabe::AnimationControl(float second)
{

}