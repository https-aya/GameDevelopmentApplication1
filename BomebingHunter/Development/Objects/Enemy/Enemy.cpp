#include "Enemy.h"
#include "EnemyBullet.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), max_animation(0), anime_time(0), shot_count(0),shot_rand(0),alpha(0),blend_flag(FALSE),sco(0)
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
	case eBoxEnemy:
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = 10;
		break;
	case eFlyEnemy:
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = 10;
		break;
	case eHarpy:
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		box_size = 64.0f;
		sca = -20;
		break;
	case eGoldEnemy:
		animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
		animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
		animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
		animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
		box_size = 32.0f;
		sca = 100;
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
	
	float random = (GetRand(10) + 10.0f) / 10.0f;

	if (location.x >= 50.0f)
	{
		random *= -1;
	}

	sco = sca;

	//向きの設定
	radian = 0.0;

	//大きさの設定
	shot_rand = 100;

	//初期画像の設定
	image = animation[0];
	
	//透明度の初期値
	alpha = 255;

	fly_text->Initialize();

	//初期進行方向の設定
	SetDirection(Vector2D(random, 0.0f));
}

//更新処理
void Enemy::Update()
{
	if (blend_flag == FALSE)
	{
		shot_count++;

		if (type == 3)
		{
			if (shot_count >= shot_rand)
			{
				shot_flag = TRUE;
				shot_count = 0;
				shot_rand = (GetRand(2) + 1) * 100;
			}
			else
			{
				shot_flag = FALSE;
			}
		}
		if (location.x < 0 || location.x > 630)
		{
		Finalize();
		}
	}
	else
	{
		shot_flag = FALSE;
	}

	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();

	if (alpha <= 0)
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

	if (blend_flag == TRUE)
	{
		fly_text->Draw(location, sco);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
	location = NULL;
	Delete = TRUE;
}

//当たった時の処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == eBome)
	{
		fly_text->SetFlyText(sco);
		blend_flag = TRUE;
		box_size = NULL;
		direction = Vector2D(0.0f,0.1f);
		sca = 0;
	}
}

void Enemy::Movement()
{
	location += direction;
}

void Enemy::AnimeControl()
{
	if (blend_flag == TRUE)
	{

		alpha-=2;
	}
	else
	{
		//アニメーションカウントを加算する
		animation_count++;

		//60フレーム目に到達したら
		if (animation_count >= 30)
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
}