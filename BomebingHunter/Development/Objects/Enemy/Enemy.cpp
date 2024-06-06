#include "Enemy.h"
#include "EnemyBullet.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), max_animation(0), anime_time(0), shot_count(0),shot_rand(0)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}
}

Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize() 
{
	switch (type)
	{
	case 3:
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		break;
	case 4:
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		break;
	case 5:
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		break;
	case 6:
		animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
		animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
		animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
		animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
		box_size = 32.0f;
		break;
	}

	for (int i = 0; i < 5; i++)
	{
		if (animation[i] != NULL)
		{
			max_animation++;
		}
		else if (animation[i] == -1)
		{
			throw("エネミーの画像がありません\n");
		}
	}
	
	float random = (GetRand(20) + 1.0) / 10;

	if (location.x >= 590.0f)
	{
		random *= -1;
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	shot_rand = 100;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	SetDirection(Vector2D(random, 0.0f));
}

//更新処理
void Enemy::Update()
{
	shot_count++;

	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

	if (shot_count >= 100)
	{
		shot_flag = TRUE;
		shot_count = 0;
		shot_rand = (GetRand(3) + 1) * 100;
	}
	else
	{
		shot_flag = FALSE;
	}

	if (location.x < 0)
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
	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	//画像の削除
	for (int i = 0 ; i < 5 ; i++)
	{
		DeleteGraph(animation[i]);
	}
	box_size = NULL;
	direction = 0.0f;
	location = NULL;
	Delete = TRUE;
}

//当たった時の処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	Finalize();
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
		anime_time++;

		//画像の切り替え
		if (image == animation[max_animation - 1])
		{
			anime_time = 0;
			image = animation[0];
		}
		else
		{
			image = animation[anime_time];
		}

	}
}