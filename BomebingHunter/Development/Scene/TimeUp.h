#pragma once

#include <vector>

class TimeUp
{
private:
	std::vector<int> image;			//評価の画像
	int draw;						//表示する画像
	int count;						//画像切り替え用のカウント

public:
	//コンストラクタ
	TimeUp();
	//デストラクタ
	~TimeUp();

	//初期化処理
	void Initialize();
	//更新処理（ゲットしたスコアで表示する画像を変更する）
	void Update(int sco);
	//描画処理
	void Draw() const;
	//終了時処理
	void Finalize();
};

