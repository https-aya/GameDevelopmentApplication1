#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize() 
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ボックスエネミーの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(-1.0f, 0.0f);
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

	if (location.x < 60)
	{
		Finalize();
	}
}

//描画処理
void Enemy::Draw() const
{
	int flip_flag = FALSE;

	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	//画像の削除
	for (int i = 0 ; i < 2 ; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たった時の処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	direction = 0.0f;
}

void Enemy::Movement()
{



	location += direction;
}

void Enemy::AnimeControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}