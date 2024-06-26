#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0),flip_flag(FALSE)
{

}

//デストラクタ
Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	//画像の読み込み
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Tri-pilot/1.png");
	animation.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Tri-pilot/2.png");
	animation.push_back(tmp[0]);

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();

}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);
}

//終了時処理
void Player::Finalize()
{
	//動的配列の開放
	animation.clear();
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{

}

//移動処理
void Player::Movement()
{
	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		if (location.x > 30.0f)
		{
			direction.x = -2.0f;
			flip_flag = TRUE;
		}
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		if (location.x < 610.0f)
		{
			direction.x = 2.0f;
			flip_flag = FALSE;
		}
	}
	else
	{
		direction.x = 0.0f;
	}

	//現在の位置座標に速さを加算する
	location += direction;
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームレートを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
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