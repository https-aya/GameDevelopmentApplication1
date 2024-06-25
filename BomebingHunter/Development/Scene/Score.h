#pragma once

#include "../Objects/GameObject.h"

class Score
{
private:
	int score;
	int high_score;
	int number_image[11];
	int font_image[3];
	int scores[10];
	int high_scores[10];
	int times[2];
	int score_size[2];

public:
	Score();
	~Score();

	void Initialize();
	void Update(int timer);
	void Draw() const;
	void Finalize();


	void SetScore(int scr);
	int GetScore() const;
	void SetHighScore();
};

