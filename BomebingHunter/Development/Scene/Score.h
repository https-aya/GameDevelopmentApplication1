#pragma once

#include <vector>

#define FLAME_RATE (144)

class Score
{
private:
	int score;							//スコア
	int high_score;						//ハイスコア
	std::vector<int> number_image;		//数字の画像
	std::vector<int> font_image;		//文字の画像
	int score_digit[10];				//スコアを桁ごとに保存する
	int high_score_digit[10];			//ハイスコアを桁ごとに保存する
	int score_digit_size;				//スコアの桁の数
	int high_score_digit_size;			//ハイスコアの桁数
	int time_digit[2];					//時間をけたごとに保存する
	int time;							//時間
	int count_time;						//時間を減らすタイミングを測る

public:
	//コンストラクタ
	Score();
	//デストラクタ
	~Score();		

	//初期化処理
	void Initialize();
	//更新処理
	void Update();	
	//描画処理
	void Draw() const;	
	//終了時処理
	void Finalize();		

	//スコア変更処理
	void SetScore(int scr);	
	//スコア取得処理
	int GetScore() const;	
	//ハイスコア変更処理
	void SetHighScore();	
	//時間取得処理
	int GetTime() const;
};

