#pragma once

#include "../Utility/Vector2D.h"
#include <vector>

class FlyText
{
private:
	std::vector<int> number_image;	//数字の画像
	int fly_text_digit[3];			//数字を桁ごとに保存
	int digit_size;					//桁数
	int score;						//表示するスコア

public:
	//コンストラクタ
	FlyText();
	//デストラクタ
	~FlyText();

	//初期化処理
	void Initialize();
	//描画処理
	//@param location:描画する座標
	//@param sco:描画する点数
	void Draw(Vector2D location) const;
	//終了時処理
	void Finalize();
	//点数の変更処理
	void SetFlyText(int ft);

};

