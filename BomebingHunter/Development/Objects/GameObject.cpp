#include "GameObject.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	direction(0.0f),
	radian(0.0),
	image(0),
	sound(0),
	type(),
	Delete(FALSE),
	shot_flag(FALSE),
	score(0)
{
}

//デストラクタ
GameObject ::~GameObject()
{
}

//初期化処理
void GameObject::Initialize()
{
}

//更新処理
void GameObject::Update()
{
}

//描画処理
void GameObject::Draw() const
{
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif //D_PIVOT_CENTER
}

//終了時処理
void GameObject::Finalize()
{
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

Vector2D GameObject::GetScale() const
{
	return box_size;
}

int GameObject::GetType() const
{
	return type;
}

bool GameObject::GetDelete() const
{
	return Delete;
}

void GameObject::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
}

Vector2D GameObject::GetDirection() const
{
	return direction;
}

void GameObject::SetType(const ObjectType type)
{
	this->type = type;
}

bool GameObject::GetShotFlag() const
{
	return shot_flag;
}

int GameObject::GetScore() const
{
	return score;
}