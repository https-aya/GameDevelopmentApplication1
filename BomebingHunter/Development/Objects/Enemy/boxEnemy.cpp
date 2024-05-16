#include "boxEnemy.h"
#include "DxLib.h"

boxEnemy::boxEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

boxEnemy::~boxEnemy()
{
}

//初期化処理
void boxEnemy::Initialize() 
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	float randam = (GetRand(20) + 1.0) / 10;


	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("ボックスエネミーの画像がありません\n");
		}
	}
	

	if (location.x >= 590.0f)
	{
		randam *= -1;
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(randam, 0.0f);
}

//更新処理
void boxEnemy::Update()
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
void boxEnemy::Draw() const
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
void boxEnemy::Finalize()
{
	//画像の削除
	for (int i = 0 ; i < 2 ; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たった時の処理
void boxEnemy::OnHitCollision(GameObject* hit_object)
{
}

void boxEnemy::Movement()
{
	location += direction;
}

void boxEnemy::AnimeControl()
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
		else if(image == animation[1])
		{
			image = animation[0];
		}
	}
}