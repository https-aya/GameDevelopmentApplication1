#include "WingEnemy.h"
#include "DxLib.h"

WingEnemy::WingEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

WingEnemy::~WingEnemy()
{
}

//初期化処理
void WingEnemy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	float randam = (GetRand(20) + 1.0) / 10;

	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("ボックスエネミーの画像がありません\n");
		}
	}

	if (location.x >= 500.0f)
	{
		randam *= -1;
	}
	
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(randam, 0.0f);
}

//更新処理
void WingEnemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

	if (location.x < 0)
	{
		Finalize();
	}
}

//描画処理
void WingEnemy::Draw() const
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

	//デバッグ用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void WingEnemy::Finalize()
{
	//画像の削除
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たった時の処理
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
}

void WingEnemy::Movement()
{
	location += direction;
}

void WingEnemy::AnimeControl()
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
		else if (image == animation[1])
		{
			image = animation[0];
		}

		if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[2];
		}
	}
}