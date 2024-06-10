#pragma once
class Score
{
private:
	int score_image[10];
	int font_image[2];
	int score[10];
	int high_score[10];
	int score_size;

public:
	Score();
	~Score();

	void Initialize();
	void Update(int scr);
	void Draw() const;
	void Finalize();

};

