#pragma once
class Score
{
private:
	int score;
	int high_score;
	int score_image[10];
	int font_image[2];
	int scores[10];
	int high_scores[10];
	int score_size[2];

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	void SetScore(int scr);
	int GetScore() const;
	void SetHighScore();
};

