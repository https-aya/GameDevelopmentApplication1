#include "Bomb.h"
#include "DxLib.h"

Bomb::Bomb() : direction(0.0f), animation(NULL)
{
}

Bomb :: ~Bomb()
{

}

void Bomb::Initialize()
{
	animation = LoadGraph("Resource/Images/Bomb/Bomb.png");

	if (animation == -1)
	{
		throw("ƒ{ƒ€‚Ì‰æ‘œ‚ª‚ ‚è‚Ü‚¹‚ñ");
	}



	radian = 90 * (3.14/180);

	box_size = 32.0;

	direction = Vector2D(0.0f, 1.0f);

	image = animation;
}

void Bomb::Update()
{
	Movement();

	if (location.y >= 400)
	{
		Finalize();
	}
}

void Bomb::Draw() const
{

	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE);
	__super::Draw();
}

void Bomb::Finalize()
{
	direction = 0.0f;
	box_size = NULL;
	location = NULL;
	DeleteGraph(animation);
}

void Bomb::OnHitCollision(GameObject* hit_object)
{

	Finalize();
}

void Bomb::Movement()
{
	location += direction;
}
