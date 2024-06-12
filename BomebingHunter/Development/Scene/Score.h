#pragma once
class Score
{
private:
	int score;
	int score_image[10];
	int font_image[2];
	int scores[10];
	int high_scores[10];
	int score_size;

public:
	Score();
	~Score();

	void Initialize();
	void Update(int scr);
	void Draw() const;
	void Finalize();

	void SetScore(int scr);

};

