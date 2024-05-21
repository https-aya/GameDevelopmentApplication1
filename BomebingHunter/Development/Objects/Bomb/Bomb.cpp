#include "Bomb.h"
#include "DxLib.h"

Bomb :: Bomb() : animation(NULL),direction(0.0f)
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
		throw("�{���̉摜������܂���");
	}

	radian = 90 * (3.14/180);

	box_size = 32.0;

	direction = Vector2D(0.0f, 1.0f);

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

	DrawRotaGraphF(location.x, location.y, 0.5, radian, animation, TRUE);

	__super::Draw();
}

void Bomb::Finalize()
{
	box_size = NULL;
	location = NULL;
	direction = 0.0f;
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